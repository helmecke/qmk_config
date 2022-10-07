# qmk_config

> Drashna — Today at 12:13 AM
> but it's ... definitely a bit convoluted
> Drashna — Today at 12:15 AM
> basically: 
> Disable SPLIT_OLED_ENABLE, this syncs the status, but is wrong.  It syncs it based on the on/off status, but it alwayr returns false if there is no oled.
> so you have to manually track and check
> but the best way to do that is to also... disable the oled timeout and handle that yourself
> So, I track the timeout manually: 
> https://github.com/qmk/qmk_firmware/blob/master/users/drashna/oled/oled_stuff.c#L107-L117, and the oled_timer_reset is also triggered by mouse movement (in the pointing_device_task_user function), which you may want to do too. 
> 
> From there, I set a boolean based on if it should be turned on or off: 
> https://github.com/qmk/qmk_firmware/blob/master/users/drashna/oled/oled_stuff.c#L996-L998
> This logic is set independent of if the oled is present or not. 
> 
> 
> And then I use that boolean to turn the oled on or off:
> https://github.com/qmk/qmk_firmware/blob/master/users/drashna/oled/oled_stuff.c#L933-L942
> the trick is that I also use the custom data sync option to sync the boolean status to the slave side.  And since that sets the boolean that is already being checked....
> https://docs.qmk.fm/#/feature_split_keyboard?id=custom-data-sync
> you can see what I sync it, at: 
> https://github.com/qmk/qmk_firmware/blob/master/users/drashna/split/transport_sync.c#L99
> And:
> https://github.com/qmk/qmk_firmware/blob/master/users/drashna/split/transport_sync.c#L123
