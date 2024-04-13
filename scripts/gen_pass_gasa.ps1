Clear-Host

$target_arch        = Join-Path $PSScriptRoot 'helpers/target_arch.psm1'
$devshell           = Join-Path $PSScriptRoot 'helpers/devshell.ps1'
$format_cpp	        = Join-Path $PSScriptRoot 'helpers/format_cpp.psm1'
$incremental_checks = Join-Path $PSScriptRoot 'helpers/incremental_checks.ps1'
$vendor_toolchain   = Join-Path $PSScriptRoot 'helpers/vendor_toolchain.ps1'
$update_deps        = Join-Path $PSScriptRoot 'update_deps.ps1'

$path_root     = git rev-parse --show-toplevel

Import-Module $target_arch
Import-Module $format_cpp

#region Arguments
$vendor       = $null
$release      = $null
$verbose      = $false
[bool] $bootstrap    = $false
[bool] $singleheader = $false
[bool] $test         = $false

[array] $vendors = @( "clang", "msvc" )

# This is a really lazy way of parsing the args, could use actual params down the line...

if ( $args ) { $args | ForEach-Object {
	switch ($_){
	{ $_ -in $vendors }   { $vendor       = $_; break }
	"verbose"			  { $verbose      = $true }
	"release"             { $release      = $true }
	"debug"               { $release      = $false }
	}
}}
#endregion Arguments

#region Configuration
if ($IsWindows) {
	# This library was really designed to only run on 64-bit systems.
	# (Its a development tool after all)
    & $devshell -arch amd64
}

if ( $vendor -eq $null ) {
	write-host "No vendor specified, assuming clang available"
	$compiler = "clang"
}

if ( $release -eq $null ) {
	write-host "No build type specified, assuming debug"
	$release = $false
}
elseif ( $release -eq $false ) {
	$debug = $true
}
else {
	$optimize = $true
}


. $vendor_toolchain
. $incremental_checks

write-host "Building GasaGen with $vendor"
write-host "Build Type: $(if ($release) {"Release"} else {"Debug"} )"

#region Building
$path_project  = Join-Path $path_root    'Project'
$path_binaries = Join-Path $path_project 'Binaries'
$path_scripts  = Join-Path $path_root    'scripts'
$path_source   = Join-Path $path_project 'Source'

$path_gasa    = join-path $path_source   'Gasa'
$path_gasagen = join-path $path_source   'GasaGen'
$exe_gasagen  = join-path $path_binaries 'GasaGen.exe'

function build-gengasa
{
	$includes   = @( $path_gasagen )
	$unit       = join-path $path_gasagen 'GasaGen.cpp'

	$compiler_args = @()
	$compiler_args += ($flag_define + 'GEN_TIME')

	$linker_args = @()
	$linker_args += $flag_link_win_subsystem_console

	build-simple $path_binaries $includes $compiler_args $linker_args $unit $exe_gasagen
}
build-gengasa

function run-gengasa
{
	Push-Location $path_project
	if ( Test-Path( $exe_gasagen ) ) {
		write-host "`nRunning GasaGen"
		$time_taken = Measure-Command { & $exe_gasagen
				| ForEach-Object {
					write-host `t $_ -ForegroundColor Green
				}
			}
		write-host "`GasaGen completed in $($time_taken.TotalMilliseconds) ms"
	}
	Pop-Location

	$path_AbilitySystem = join-path $path_gasa 'AbilitySystem'
	$include  = @(
		'GasaAttributeSet.h', 'GasaAttributeSet.cpp'
	)
	format-cpp $path_AbilitySystem $include $null
}
run-gengasa
