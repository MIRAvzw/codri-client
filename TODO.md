Short term
==========

Simplification
--------------

Simplify the god damn thing! Event and data propagation is too damn
complicated right now.



State machine log messages
--------------------------

The current state machine logic is completely opaque: no debug messages are
generated when the state machine switches states. It would be very interesting
if we could at lease optionally debug this logic in order to have a better
understanding of the application state when something goes haywire.


Syslog
------

Log all messages to syslog, and filter them into /var/log/codri using a
rsyslog rule.




Medium term
===========

Platform abstraction
--------------------

Properly isolate platform specific details and move them behind interfaces



Long term
=========

QtWebKit
--------

Move back to QtWebKit, it provides way better integration and allows to
register non-standard Javascript objects (allowing to display application-
specific data).

However, QtWebKit was _way_ too slow to render the Planetarium demo decently.
This might improve when we use a optimized (NEON/OpenGL-ES2 enabled) Qt build,
but I fear that the Javascript interpreter itself is pretty crap.
