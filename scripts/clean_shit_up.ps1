# PowerShell script to remove Content directory from Git history
Clear-Host

# Script setup
$ErrorActionPreference = "Stop"
$VerbosePreference = "Continue"

# Path setup
$path_scripts = $PSScriptRoot
$path_helpers = Join-Path $path_scripts 'helpers'
$path_root    = Split-Path -Parent -Path $path_scripts
$path_project = Join-Path $path_root 'Project'
$path_content = Join-Path $path_project 'Content'

# Function to remove Content directory from Git history
function Remove-ContentFromGitHistory {
    param([string]$repoPath)

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

    # Navigate to repository root
    Push-Location $repoPath

    try {
        Write-Verbose "Removing Content directory from Git history..."
        
        # Construct and execute filter-branch command
        $filter_branch_args = @(
            $fgit_force,
            $fgit_index_filter,
            "git rm -r $fgit_cached $fgit_ignore_unmatch `"$path_content`"",
            $fgit_prune_empty,
            $fgit_tag_name_filter,
            $fgit_filter_concat,
            $fgit_filter_separate,
            $fgit_all
        )
        & git $cgit_filter_branch $filter_branch_args
        if ($LASTEXITCODE -ne 0) { throw "Error during filter-branch operation" }

        Write-Verbose "Cleaning up refs..."
        # Clean up refs
        $for_each_ref_args = @("$fgit_format='$fmt_delete_refs'", $original_refs)
        $refs_to_delete = & git $cgit_for_each_ref $for_each_ref_args
        $refs_to_delete | & git $cgit_update_ref $fgit_stdin
        if ($LASTEXITCODE -ne 0) { throw "Error during ref cleanup" }

        Write-Verbose "Expiring reflog..."
        # Expire reflog
        $reflog_expire_args = @($fgit_expire_now, $fgit_all)
        & git $cgit_reflog_expire $reflog_expire_args
        if ($LASTEXITCODE -ne 0) { throw "Error during reflog expiration" }

        Write-Verbose "Running garbage collection..."
        # Garbage collection
        $gc_args = @($fgit_prune_now, $fgit_aggressive)
        & git $cgit_garbage_collect $gc_args
        if ($LASTEXITCODE -ne 0) { throw "Error during garbage collection" }

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
Remove-ContentFromGitHistory $path_root

Write-Host "Script execution completed. Please review your repository to ensure the desired outcome."
Write-Host "Remember to force-push these changes if you want to update the remote repository."
