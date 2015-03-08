# Windows Host Software

My limited understanding is that most Windows cryptography uses 
Microsoft's "Crypto API." The routine for getting random entropy is 
CryptGenRandom() as described here:
	https://msdn.microsoft.com/en-us/library/windows/desktop/aa379942%28v=vs.85%29.aspx
	
It would be nice if someone figured out how to get REDOUBLER bits merged 
there. Of course the REDOUBLER is available as a microphone input. Look 
under
	Start, Control Panel, Sound, Recording There is a listen option 
that can be activated by checking the box and pressing "Apply." I don't 
currently know of a way to record bytes without volume adjustment and/or 
mixing. Audacity sees the device and can record, but it seems to mangle 
it, at
least a little.
