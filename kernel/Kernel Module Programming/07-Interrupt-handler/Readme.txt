As seen, the earlier manual waiting has been replaced by single statement wait_event_interruptible() which is more robust.
The process will wake up only if the flag is set to ‘y’
