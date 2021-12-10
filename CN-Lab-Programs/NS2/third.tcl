# Copyright (C) 2021 Kritik Agarwal <https://github.com/Kritik007>

# Simulate the transmission of ping messages over a network topology 
# consisting of 6 nodes and find the number of packets dropped due to congestion.

set ns [new Simulator]
set nf [open PING.nam w]
$ns namtrace-all $nf
set nt [open PING.tr w]
$ns trace-all $nt

proc finish {} {
            global ns nf nt
            $ns flush-trace
            close $nf
               close $nt
            exec nam PING.nam &
		  exec awk -f third.awk PING.tr &
            exit 0
     }

# Create six nodes

   set n0 [$ns node]
   set n1 [$ns node]
   set n2 [$ns node]
   set n3 [$ns node]
   set n4 [$ns node]
   set n5 [$ns node]

# Connect the nodes with two links    

   $ns duplex-link $n0 $n1 1Mb 10ms DropTail
   $ns duplex-link $n2 $n1 1Mb 10ms DropTail
   $ns duplex-link $n3 $n1 1Mb 10ms DropTail
   $ns duplex-link $n4 $n1 1Mb 10ms DropTail
   $ns duplex-link $n5 $n1 1Mb 10ms DropTail

#Label the nodes     

   $n0 label "ping0"
   $n1 label "Router"
   $n2 label "ping2"
   $n3 label "ping3"
   $n4 label "ping4"
   $n5 label "ping5"

#Color the flow

   $ns color 2 Blue
   $ns color 3 Red
   $ns color 4 Yellow
   $ns color 5 Green

#Define s ‘recv’ function for the class ‘Agent/Ping’    

   Agent/Ping instproc recv {from rtt} {
      $self instvar node_
      puts "node [$node_ id] received ping answer from \
      $from with round-trip-time $rtt ms."
#
   }

#Create ping agents and attach them to the nodes     

   set p0 [new Agent/Ping]
   $ns attach-agent $n0 $p0
   $p0 set class_ 1
   
   set p2 [new Agent/Ping]
   $ns attach-agent $n2 $p2
   $p2 set class_ 2

   set p3 [new Agent/Ping]
   $ns attach-agent $n3 $p3
   $p3 set class_ 3

   set p4 [new Agent/Ping]
   $ns attach-agent $n4 $p4
   $p4 set class_ 4

   set p5 [new Agent/Ping]
   $ns attach-agent $n5 $p5
   $p5 set class_ 5

#Connect the two agents     

   $ns connect $p2 $p5
   $ns connect $p3 $p5

    proc SendPingPacket { } {
      global ns p2 p3
      set intervalTime 0.001
      set now [$ns now]
      $ns at [expr $now+$intervalTime] "$p2 send"
      $ns at [expr $now+$intervalTime] "$p3 send"
      $ns at [expr $now+$intervalTime] "SendPingPacket"
    }

      $ns at 0.1 "SendPingPacket"
      $ns at 2.0 "finish"
      $ns run

