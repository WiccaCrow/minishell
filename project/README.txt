Hello!!!
Dear friend, we are very glad that you visited our project and are now
reading README.

This project is a mini-bash written in C language.

__________________________
The start of the program begins in the minishell.c file with the main ()
function.

1. main()
1.1. start_all;
1.2. show_program_name;
1.3. fill_all;
1.4. executor;
1.5. exit_clean;
__________________________

1.1. start_all;
		Start program with zero-structure (example, pointers = NULL, 
		int variables = 0).
1.2. show_program_name.
		Prints the name of the program to standard output (terminal). 
		In our program, this will happen every time the shell is waiting 
		for a command from the user.

1.3. fill_all.
		This function performs several important operations:
		1) checks the validity of the data entered by the user into the 
			shell command line, sets the data validity flag in the t_all 
			structure.

			flag:
			1 - data is not valid.

		2) based on these data, fills in the main structure of the 
			program. t_all all.
1.4. executor.
		Accepts a data-ready structure.
		Checks the flags of the operations in the structure.
		Applies functions corresponding to flags to data.
		Prints the result or error to standard output as needed.

		flags and functions:
		 1 - 	data is not valid.
		 2 - 	echo with option ’-n’
		 3 - 	cd with only a relative or absolute path
		 4 - 	pwd without any options
		 5 - 	export without any options
		 6 - 	unset without any options
		 7 - 	env without any options and any arguments 
		 8 -	exit without any options
		 9 - 	ctrl-C
		10 - 	ctrl-D
		11 - 	ctrl- \
		12 - 	

