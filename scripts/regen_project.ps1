Clear-Host

$path_scripts = $PSScriptRoot
$path_helpers = join-path $path_scripts 'helpers'
$path_root    = split-path -Parent -Path $path_scripts
$path_ue      = join-path '../../Surgo' 'UE'
$path_project = join-path $path_root 'Project'

$uproject = join-path $path_project 'Gasa.uproject'

$UBT = join-path $path_ue 'Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe'

$fubt_project      = '-project'
$fubt_projectfiles = '-projectfiles'
$fubt_game         = '-game'
$fubt_engine       = '-engine'
$fubt_progress     = '-progress'

$ubt_args  = @()
$ubt_args += $fubt_projectfiles
$ubt_args += "$fubt_project=$uproject"
$ubt_args += $fubt_game
$ubt_args += $fubt_engine
$ubt_args += $fubt_progress
& $UBT $ubt_args
