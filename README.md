# PassPolicyFilter
Custom filter for AD Domain Controllers that reads from wordlist


## Setup:

1. Copy PassFilter.dll to **C:\Windows\System32\** directory
2. Open Reg Edit **(regedit.exe)** and find HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Lsa\Notification Packages
3. In Notification Packages add PassFilter at the end of the list. (Without the .dll extension)
   
   If the Notification Packages value of type REG_MULTI_SZ exists, add the name of your DLL to the existing value data. Do not overwrite the existing values, and do not include the .dll      extension.
   
   If the Notification Packages value does not exist, create it, give it the REG_MULTI_SZ type and then specify the name of the DLL for the value data. Do not include the .dll extension.
   The Notification Packages value can add multiple packages.

5. Find the password complexity setting.
   
   In Control Panel, click Performance and Maintenance, click Administrative Tools, double-click Local Security Policy, double-click Account Policies, and then double-click Password Policy.

6. To enforce both the default Windows password filter and the custom password filter, ensure that the Passwords must meet complexity requirements policy setting is enabled. Otherwise, disable the Passwords must meet complexity requirements policy setting.   

7. Save changes & restart DC
