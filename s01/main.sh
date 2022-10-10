#! /bin/bash

#### 1 ####
echo "$(tput setaf 0) $(tput setab 30) First part: $(tput sgr 0)"
echo -e "\tThe commnad is: $(tput setab 1) ls -l $(tput sgr 0) or $(tput setab 1) dir -l $(tput sgr 0)\n"
echo -e "\tThe commnad is: $(tput setab 1) find . -maxdepth 1 -type d | grep " " | xargs echo >> documnet.txt $(tput sgr 0)\n"
echo -e "\tThe commnad is: $(tput setab 1) cd ~ $(tput sgr 0) or $(tput setab 1) cd /home/\$USER $(tput sgr 0)\n"
echo -e "\tThe commnad is: $(tput setab 1) touch filename $(tput sgr 0) or $(tput setab 1) echo > filename $(tput sgr 0)\n"
echo -e "\tThe commnad is: $(tput setab 1) stat filename $(tput sgr 0) or $(tput setab 1) ls filename -l $(tput sgr 0)\n"
echo -e "\tThe commnad is: $(tput setab 1) vim filename $(tput sgr 0)\n"
echo -e "\tThe commnad is: $(tput setab 1) sudo cp filename /root $(tput sgr 0) or $(tput setab 1) sudo cat filename > /root/filename $(tput sgr 0)\n"
echo -e "\tThe commnad is: $(tput setab 1) sudo chmod a-w /root/filename $(tput sgr 0) or $(tput setab 1) sudo chmod -444 /root/filename $(tput sgr 0)\n"

#### 2 ####
echo "$(tput setaf 0) $(tput setab 30) Second part: $(tput sgr 0)"
echo -e "\tThe commnad is: $(tput setab 1) ifconfig $(tput sgr 0) or $(tput setab 1) ip addr show $(tput sgr 0)\n"
echo -e "\tThe commnad is: $(tput setab 1) ssh \$friend_ipaddress $(tput sgr 0)\n"
echo -e "\tThe commnad is: $(tput setab 1) scp /root/\$friend_filename \$your_username@\$your_ipaddress:\$file_path $(tput sgr 0)\n"

#### 3 ####
echo "$(tput setaf 0) $(tput setab 30) Third part: $(tput sgr 0)"
echo -e "\tThe commnad is: $(tput setab 1) top -b -o +%MEM | head -n 10 | tail -n 3 | awk {'print $12'} >> document.txt $(tput sgr 0)\n"
echo -e "\tThe commnad is: $(tput setab 1) ps aux | grep migration $(tput sgr 0)\n"

#### 4 ####
echo "$(tput setaf 0) $(tput setab 30) Fourth part: $(tput sgr 0)"
echo -e "\tThe commnad is: $(tput setab 1) sudo apt-get install linux-source $(tput sgr 0)\n"
echo -e "\tThe commnad is: $(tput setab 1) sudo tar xvf /usr/src/*.tar* $(tput sgr 0)\n"
echo -e "\tThe commnad is: $(tput setab 1) find /usr/src -name syscall.tbl $(tput sgr 0)\n"
echo -e "\tThe commnad is: $(tput setab 1) cat \`find /usr/src -name syscall.tbl\` | grep write | wc -l $(tput sgr 0)\n"
echo -e "\tThe commnad is: $(tput setab 1) cat \`find /usr/src -name syscall.tbl\` | grep write > filename2 $(tput sgr 0)\n"