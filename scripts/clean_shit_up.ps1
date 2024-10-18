# PowerShell script to remove Content directory from Git history
clear-host

# Script setup
$ErrorActionPreference = "Stop"
$VerbosePreference     = "Continue"

# Path setup
$path_scripts = $PSScriptRoot
$path_helpers = Join-Path $path_scripts 'helpers'
$path_root    = Split-Path -Parent -Path $path_scripts
$path_project = Join-Path $path_root 'Project'
$path_content = Join-Path $path_project 'Content'

# Function to remove Content directory from Git history
function Remove-ContentFromGitHistory {
    param([string]$path_repo)

    # Git commands and flags
    $cgit_filter_branch   = 'filter-branch'
    $cgit_for_each_ref    = 'for-each-ref'
    $cgit_update_ref      = 'update-ref'
    $cgit_reflog_expire   = 'reflog expire'
    $cgit_garbage_collect = 'gc'

    $fgit_aggressive      = '--aggressive'
    $fgit_all             = '--all'
    $fgit_cached          = '--cached'
    $fgit_format          = '--format'
    $fgit_expire_now      = '--expire=now'
    $fgit_ignore_unmatch  = '--ignore-unmatch'
    $fgit_index_filter    = '--index-filter'
    $fgit_force           = '--force'
    $fgit_prune_empty     = '--prune-empty'
    $fgit_prune_now       = '--prune=now'
    $fgit_tag_name_filter = '--tag-name-filter'
    $fgit_stdin           = '--stdin'

    $fgit_filter_concat   = 'cat'
    $fgit_filter_separate = '--'

    $fmt_delete_refs = 'delete %(refname)'
    $original_refs   = 'refs/original'

    Write-Verbose "Received path_repo: $path_repo"

    if ([string]::IsNullOrWhiteSpace($path_repo)) {
        throw "Repository path is null or empty"
    }

    if (-not (Test-Path $path_repo)) {
        throw "Repository path does not exist: $path_repo"
    }

    # Navigate to repository root
    Push-Location $path_repo

    try {
        Write-Verbose "Current directory: $(Get-Location)"

        # Check if we're in a git repository
        if (-not (Test-Path (Join-Path $path_repo '.git'))) {
            throw "Not in a git repository. Please run this script from the root of your git repository."
        }

        # Check if the Content directory exists
        if (-not (Test-Path $path_content)) {
            throw "Content directory not found at $path_content"
        }

        # Get the relative path of the content directory
        $path_content_relative = Resolve-Path -Relative -Path $path_content
        Write-Verbose "Relative content path: $path_content_relative"

        Write-Verbose "Removing Content directory from Git history..."

        # Construct and execute filter-branch command
        $filter_command = "git rm -r --cached --ignore-unmatch `"$path_content_relative`""
        $filter_branch_cmd = "git $cgit_filter_branch $fgit_force $fgit_index_filter '$filter_command' $fgit_prune_empty $fgit_tag_name_filter $fgit_filter_concat $fgit_filter_separate $fgit_all"
        Write-Verbose "Executing command: $filter_branch_cmd"
        $output = Invoke-Expression $filter_branch_cmd 2>&1
        $output | ForEach-Object {
            if ($_ -match "WARNING:") {
                Write-Warning $_
            } elseif ($_ -match "fatal:") {
                throw $_
            } else {
                Write-Verbose $_
            }
        }

        Write-Verbose "Cleaning up refs..."
        # Clean up refs using git directly
        $refs = & git show-ref --heads | ForEach-Object { $_.Split()[1] }
        foreach ($ref in $refs) {
            $originalRef = "$original_refs/$ref"
            if (& git show-ref --verify --quiet $originalRef) {
                Write-Verbose "Deleting ref: $originalRef"
                & git update-ref -d $originalRef
            }
        }

        # Remove any remaining refs/original directory
        $originalRefsPath = Join-Path $path_repo ".git\$original_refs"
        if (Test-Path $originalRefsPath) {
            Write-Verbose "Removing refs/original directory"
            Remove-Item -Recurse -Force $originalRefsPath
        }

        Write-Verbose "Expiring reflog..."
        & git reflog expire $fgit_expire_now $fgit_all

        Write-Verbose "Running garbage collection..."
        & git gc $fgit_prune_now $fgit_aggressive

        Write-Verbose "Content removal from Git history completed successfully."
    }
    catch {
        Write-Error "An error occurred: $_"
    }
    finally {
        Pop-Location
    }
}

# Main execution
Write-Host "This script will remove the Content directory from your Git history."
Write-Host "This action is IRREVERSIBLE. Make sure you have a backup before proceeding."
$confirmation = Read-Host "Are you sure you want to continue? (y/n)"
if ($confirmation -ne 'y') {
    Write-Host "Operation cancelled."
    exit
}

# Execute the function
Write-Verbose "Calling Remove-ContentFromGitHistory with path_root: $path_root"
Remove-ContentFromGitHistory $path_root

Write-Host "Script execution completed. Please review your repository to ensure the desired outcome."
Write-Host "Remember to force-push these changes if you want to update the remote repository."
