gd-captcha
==========

Very simple CAPTCHA generator in C using GD, compatible with ejabberd.

Note for ejabberd users: full path to the font file has to be specified in `CAPTCHA_FONT_LOCATION` (because ejabberd does not chdir to the captcha program directory before running it).

Single argument: captcha text. You may adjust other options right in the source code.

Output format: [PNG](http://en.wikipedia.org/wiki/Portable_Network_Graphics).

Requirements: [libgd](http://libgd.bitbucket.org/).

License: 3-clause BSD (see [LICENSE](LICENSE)).

Example:
![beAtLes](example.png)
