# PowerShell script to set up Git LFS for Content directory
clear-host

$path_scripts = $PSScriptRoot
$path_helpers = join-path $path_scripts 'helpers'
$path_root    = split-path -Parent -Path $path_scripts
$path_ue      = join-path '../../Surgo' 'UE'
$path_project = join-path $path_root 'Project'


# Set your repository paths here
$path_content = join-path $path_project 'Content'


# Function to remove Content directory from Git history
function Remove-ContentFromGitHistory {
    push-location $path_repo

	$cgit_filter_branch   = 'filter-branch'
	$cgit_for_each_ref    = 'for-each-ref'
	$cgit_update_ref      = 'update-ref'
	$cgit_reflog_expire   = 'reflog expire'
	$cgit_garbage_collect = 'gc'

	$fgit_agressive       = '--aggressive'
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

	$fmt_delete_refs = 'delete $(refname)'
	$original_refs   = 'refs/original'

	$filter_cmd = 'git rm -r --cached'

    # Construct filter-branch command
    $filter_branch_args = @()
    $filter_branch_args += $fgit_force
    $filter_branch_args += $fgit_index_filter
    $filter_branch_args += "git rm -r $fgit_cached $fgit_ignore_unmatch $path_content"
    $filter_branch_args += $fgit_prune_empty
    $filter_branch_args += $fgit_tag_name_filter
    $filter_branch_args += $fgit_filter_concat
    $filter_branch_args += $fgit_filter_separate
    $filter_branch_args += $fgit_all

    # Execute filter-branch command
    & git $cgit_filter_branch $filter_branch_args

    # Construct for-each-ref command
    $for_each_ref_args = @()
    $for_each_ref_args += "$fgit_format='$fmt_delete_refs'"
    $for_each_ref_args += $original_refs

    # Execute for-each-ref and pipe to update-ref
    $refs_to_delete = & git $cgit_for_each_ref $for_each_ref_args
    $refs_to_delete | & git $cgit_update_ref $fgit_stdin

    # Construct and execute reflog expire command
    $reflog_expire_args = @()
    $reflog_expire_args += $fgit_expire_now
    $reflog_expire_args += $fgit_all
    & git $cgit_reflog_expire $reflog_expire_args

    # Construct and execute garbage collect command
    $gc_args = @()
    $gc_args += $fgit_prune_now
    $gc_args += $fgit_aggressive
    & git $cgit_garbage_collect $gc_args

	pop-location
}
Remove-ContentFromGitHistory
