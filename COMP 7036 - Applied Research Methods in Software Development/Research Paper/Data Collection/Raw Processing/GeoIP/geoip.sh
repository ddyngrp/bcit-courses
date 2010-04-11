#!/bin/bash

lynx -dump "http://api.hostip.info/get_html.php?ip=$1&position=true"
