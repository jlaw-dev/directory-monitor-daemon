# Directory-Monitor-Daemon
## A daemon process that watches a specified directory, logs its changes, and archives file with a date stamp.

### Using the given executable:

* You can easily use the static linked executable provided if you do not wish to deal with the library setup.
* Here's how to call the file daemon from the shell (command arguments were set up using TCLAP)
```unix
USAGE:
	./program5  [-d] [--] [--version] [-h] <config filename>

Where:
	-d,  --daemon
			Run in daemon mode
	--,  --ignore_rest
			Ignores the rest of the labeled arguments following this flag.
	--version
			Displays version information and exits.
	-h,  --help
			Displays usage information and exits.
	<config filename>
			(required) The name of the configuration file
```
* You can also recompile the daemon if necessary, but that may require changes to the Makefile's linker, library, and compiler flags.
	**NOTE: if you run the process not in daemon mode, the console will lock up and you will need to open another console to do any           further action**

### Editing the process:
* You can make changes to how the process performs by making changes to the configuraton file
**NOTE: currently the only changes that are supported by the code are changes to the logfile and watched directory**
* Changes to the daemon do not require a termination of the process, simply a signal to alert the daemon to reconfigure.

* To signal changes in the config file, use this command:
```
$ kill -1 <pid>
```     
**NOTE: The PID can be found in the pid file created by the daemon process on startup**
        
### Terminating the process:
* The process can be terminated cleanly in varying ways depending on if it is running as a daemon or not.
* If the process is running as a daemon, you may use one off two commands:
```	
$ kill -2 <pid>
$ kill -15 <pid>
```
* If the process is running in the console, you may send a signal using ^C.
* The kill 9 command does terminate the process, but not cleanly. You will have to delete the pid file manually before startup again.
	
*Libraries and APIs used: TCLAP, Rudeconfig*
