# ft_ls
The first project in 42's Systems Branch.

The goal of this project is to recode some of MacOS's ls's functionality.  The main behaviors this version must replicate are:

-R - Recursively list subdirectories encountered.

-a - Include all entries whose names begin with a '.'.

-l - List in long format.

-r - Reverse the order of the sort to get reverse lexicographical order or the oldest entries first.

-t - Sort by time modified (most recently modified first) before sorting the operands by lexicographical order.

Extra functionality added in includes:

-A - Include all entries whose names begin with a '.', excluding the "." and ".." directories.

-n - Prints out the numerical identifier for any groups and owners.  This option automatically triggers the -l flag;

To make the project, run make.
To use the project, run ./ft_ls with any of the above flags.
