# Assignment 2 on Cross-Site Scripting (XSS) Attack

## Topic:

In this assignment you will have to implement the Advanced Encryption Standard (AES)
algorithm for 128-bit key. Total marks of this assignment is 30.

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

