# Assignment 2 on Cross-Site Scripting (XSS) Attack

## Overview

Cross-site scripting (XSS) is a type of vulnerability commonly found in web applications. This
vulnerability makes it possible for attackers to inject malicious code (e.g. JavaScript programs)
into victim’s web browser. Using this malicious code, attackers can steal a victim’s credentials,
such as session cookies. The access control policies (i.e., the same origin policy) employed by
browsers to protect those credentials can be bypassed by exploiting XSS vulnerabilities.


To demonstrate what attackers can do by exploiting XSS vulnerabilities, we will use a web
application named Elgg provided in our pre-built Ubuntu VM image. In this assignment, students
need to exploit this vulnerability to launch an XSS attack on the modified Elgg. This assignment
covers the following topics:


• Cross-Site Scripting attack


• XSS worm and self-propagation


• Session cookies


• HTTP GET and POST requests


• JavaScript and Ajax


## Setting up Environment

Login to Seed Ubuntu and start the apache server.


`$sudo service apache2 start`


Vulnerable website and its source code location.


**URL: http://www.xsslabelgg.com**


Folder: /var/www/XSS/Elgg/


## Tasks


1. Becoming the Victim’s Friend [4 Marks]

2. Modifying the Victims Profile [6 Marks]

3. Posting on the Wire on Behalf of the Victim [3 Marks]

4. Design a Self-Propagating Worm [7 Marks]