# ft_ls
The first project in 42's Systems Branch.

The goal of this project is to recode some of MacOS's ls command functionality.  The main behaviors this version must replicate are:

`-R` - Recursively list subdirectories encountered.

`-a` - Include all entries whose names begin with a '.'.

`-l` - List in long format.

`-r` - Reverse the order of the sort to get reverse lexicographical order or the oldest entries first.

`-t` - Sort by time modified (most recently modified first) before sorting the operands by lexicographical order.

Note that the output mimics the output of `ls -1`, where instead of being spaced out according to the width of the terminal window, the output is listed instead.

Extra functionality added in includes:

`-A` - Include all entries whose names begin with a '.', excluding the "." and ".." directories.

`-G` - Prints with colors

`-S` - Sort by size.

`-T` - When used with `-l`, display complete time information, `MMM DD HH:MM:SS YYYY`.

`-c` - Use time when file status was last changed for sorting (`-t`) or long printing (`-l`).

`-f` - Does not sort output.  This option automatically triggers the `-a` flag.

`-n` - Prints out the numerical identifier for any groups and owners.  This option automatically triggers the `-l` flag;

`-u` - Use time of last access, instead of last modification of the file for sorting (`-t`) or long printing (`-l`).

To make the program, run `make`.
To use the program, run `./ft_ls` with any of the above flags, used in any combination.
