clear-host

$misc = join-path $PSScriptRoot 'helpers/misc.ps1'
. $misc

# Path setup
$path_scripts = $PSScriptRoot
$path_helpers = Join-Path $path_scripts 'helpers'
$path_root    = Split-Path -Parent -Path $path_scripts
$path_project = Join-Path $path_root 'Project'
$path_content = Join-Path $path_project 'Content'

$url_gasathon_content = 'https://git.cozyair.dev/ed/GASATHON_Content.git'

clone-gitrepo $path_content $url_gasathon_content
