Implementation of getgrgid and getgrnam Functions Using Low-Level System Calls
------------------------------------------------------------------------------
Overview
------------------------------------------------------------------------------
    This project implements the getgrgid and getgrnam functions, which retrieve information about user groups based on group ID (GID) and group name, respectively.
    The implementation relies on low-level system calls to parse the /etc/group file and extract the relevant group data.
------------------------------------------------------------------------------
Features
------------------------------------------------------------------------------
    Group Name Lookup (getgrnam): Retrieves a group structure based on the provided group name.
    Group ID Lookup (getgrgid): Retrieves a group structure based on the provided group ID.
    String Manipulation Functions: Custom implementations of various string functions (e.g., mystrcpy, mystrcat, mystrtok, etc.).
    File Handling: Uses system calls like open, read, and close to interact with the /etc/group file.
    Error Handling: Robust error handling with detailed messages and file/line number tracing.
-----------------------------------------------------------------------------
Project Structure
-----------------------------------------------------------------------------
    main.c: The main driver file that contains the main function and high-level program logic.
    mystring.c: Contains custom string manipulation functions used throughout the project.
    mystring.h: Header file for the custom string functions.
    group_utilities.c: Implements the core functionality of getgrgid, getgrnam, and other group-related operations.
    group_utilities.h: Header file for the group utility functions.
------------------------------------------------------------------------------
How It Works
------------------------------------------------------------------------------
    Group Lookup by Name (getgrnam):
        The program opens the /etc/group file.
        It searches for a line that starts with the specified group name.
        The line is then parsed to extract the group password, GID, and member list.
        If found, a struct group is created and returned; otherwise, NULL is returned.

    Group Lookup by GID (getgrgid):
        The program opens the /etc/group file.
        It searches for a line that contains the specified GID.
        Similar to the name lookup, the line is parsed, and a struct group is returned.
--------------------------------------------------------------------------------
Usage
--------------------------------------------------------------------------------
    Clone the repository:
      git clone https://github.com/yourusername/your-repo-name.git

    Compile the project using gcc:
      gcc -std=c99 -Wall -Wextra domaci.c mystring.c group_utilities.c -o groupinfo

    Run the program:
      ./groupinfo <group_name> <group_id>
      Replace <group_name> with the name of the group you want to look up.
      Replace <group_id> with the group ID you want to look up.
--------------------------------------------------------------------------------
Requirements
--------------------------------------------------------------------------------
    C Compiler: Ensure that GCC or any compatible C compiler is installed on your system.
