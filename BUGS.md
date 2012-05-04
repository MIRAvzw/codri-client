Critical
========

Registration controller deadlock
--------------------------------

It happened at least once that the registration state machine got in a state
of deadlock, but the trigger is not known. It happened when developing the
service code, and thus the back-end server frequently restarted (causing
multiple registration attempts to time-out).
