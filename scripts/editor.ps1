Clear-Host

$path_scripts = $PSScriptRoot
$path_helpers = join-path $path_scripts 'helpers'
$path_root    = split-path -Parent -Path $path_scripts

# Hardcoded for personal context to use existing engine in Surgo, change to desired source
$path_ue      = join-path '../../Surgo' 'UE'
$path_project = join-path $path_root 'Project'

$ue_editor = join-path $path_ue 'Engine\Binaries\Win64\UnrealEditor.exe'

$gasathon_uproject = join-path $path_project 'GASATHON.uproject'

$feditor_log = '-log'

& $ue_editor $gasathon_uproject $feditor_log
