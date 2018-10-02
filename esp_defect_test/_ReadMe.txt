Start: 15.09.2015

Complete: XX.XX.2015
___________________________________
Result: 
- 
___________________________________

ID: "US20105 Localization: Coverity-finding CID 10549."
    
___________________________________    
Description:

    CID 10549 (1 of 5): 
        Unchecked return value (CHECKED_RETURN)8. check_return: Calling system without checking return value (as is done elsewhere 5 out of 6 times).

    In file "KeyboardSettings.cpp":
    ---------------CODE-----------------
    strcpy(cmd, "setxkbmap -layout ");
    int pos = strlen(cmd); //#lint !e713 Loss of precision (return) (unsigned long to int)
    MSF_ASSERT(pos + strlen(pLayoutName) < (BUF_SIZE - 1));
    strcpy(&cmd[pos], pLayoutName);
    MSF_TRACE("keyboard", ("Keyboard setting command is '%s'", cmd));
    system(cmd);
    ---------------CODE-----------------

1.
    if (isShuttingDownCommandSentToPlatformG)
    {
        MSF_LOG("Ignoring software reset due to shutdown already running!");
    }
    else
    {
        int rv = system("/sbin/shutdown -r now");
        MSF_VERIFY(rv != -1);
    }

2.
    int rv = system("halt -n -d -f -p -C");
    MSF_VERIFY(rv != -1);


------------ 
regarding the coverity finding:
    looks like the code assumes that the system call never fails
    i wonder what happens if it does
    you probably have to test what the call does
    problem: is it inside a linux "#if" condition

    then it is a bit of a hassle to test it in the target
    a possibility: use "MSF_VERIFY" 
    still has to be tested what happens with different return values in the target
 

