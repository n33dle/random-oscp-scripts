for targets in $(echo 10.11.1.{0..255} | tr ' ' '\n'); do ping -c 2 $targets; done 
