///\page Protocol

<h1>Serial Wombat Communication Protocol</h1>

<h2><a name="Basics">Basics</a></h2>

<p>Wombat commands are all eight bytes long, and Wombat responses
are eight bytes long. The first byte is a command byte. The
meaning of following bytes varies depending on the command byte.
In some cases padding bytes are added to the end of simple
messages to achieve eight bytes. Padding bytes are set to 0x55
(see resyncing, below). Some functionality may require multiple
messages to invoke. Multi-byte values are transmitted
most-significant byte first.</p>

<h2><a name="LoosingSync">Loosing Sync</a></h2>

<p>The most important compromise of the Wombat serial protocol is
its susceptability to loss of synchronization with the host. This
can occur if the host sends a partial message or if environmental
conditions cause communication problems or a Wombat reset. If the
Wombat interprets the second or later byte of a message to be the
command (first) byte, then it will act on that byte when eight
total bytes have been received.</p>

<h2><a name="ResyncCharacter">Resync Character</a></h2>

<p>When a loss of synchronization is suspected the host should
send 0x55 (ASCII 'U' ) eight times. 0x55 is a special value which
is discarded when received as a command byte. After this sequence
is received the Wombat will always be ready to receive a command.</p>

<h2>Preventing loss of synchronization</h2>

<p>There are a number of steps the user can take to detect and
prevent loss of synchronization:</p>

<ul>
    <li>After sending a command to the Wombat wait for the Wombat
        to begin its response before sending more commands. The
        Wombat will begin sending a response within two frame
        times. If no response is sent the host and the Wombat are
        likely out of sync. It is recommended that a command not
        be sent until the first two bytes of the previous
        response have been received.</li>
    <li>Enable message checksums. This can be done with the Set
        System Status command. When checksums are enabled each
        eight byte message is followed by a ninth checksum byte.
        The value of this byte is the logical inversion (NOT) of
        the sum of the first eight bytes. The Wombat will send no
        response to a message with a bad checksum. Using
        checksums greatly reduces the chance that an out-of-sync
        message will be acted upon. This functionality is present
        in the firmware starting with version 1.1.0, but has not
        yet been documented.</li>
    <li>Enable Wombat addressing, even if only one Wombat is
        connected to the host. When addressing is enabled an
        address byte preceeds the eight byte Wombat command. When
        using addressing to increase the robustness of the Wombat
        protocol it is recommended that the address 0xFE be used.
        This value is far less frequently used in command packets
        than values such as 0x00 or 0x01. This reduces the chance
        that a byte of an out-of-sync message will be interpreted
        as the address byte. The address byte is included in the
        checksum (if enabled). Since the Wombat thinks that
        messages with a different address than its own are meant
        for another chip no response will be sent. This
        functionality is present in the firmware starting with
        version 1.1.0, but has not yet been documented.</li>
    <li>Enable intra-message timeout. The Wombat allows the host
        to define a timeout between received bytes within a
        message. If the timeout expires then the message up to
        that point will be discarded, and no response will be
        sent. This is particularly useful when checksums are
        enabled. This functionality is present in the firmware
        starting with version 1.1.0, but has not yet been
        documented.</li>
</ul>

<p>&nbsp;</p>

<table border="0">
    <tr>
        <td>For example, suppose the host intends to send two
        commands. After four bytes of the first message are sent
        an electrostatic event causes the Wombat to reset. The
        fifth byte is missed all together during the reset. The
        Wombat comes out of reset and receives the 6th, 7th, and
        8th byte of the first message, which it interprets as the
        command, 2nd and 3rd byte of a new message. The host
        waits for a response, which never comes. The Wombat
        recieve timeout occurs because a 4th byte never comes,
        and the message is discarded. The Wombat is now ready to
        receive a new message, and the host is prepared to send
        one because no response came. In following the resyncing
        recommendations above, the host will send 0x55 eight
        times, then send a new message. Note that in the above
        example the Wombat must be configured to enable receive
        timeout when coming up from reset. See the section on
        EEPROM for more information.</td>
        <td><!--webbot bot="HTMLMarkup" startspan --><!--INCLUDE <object width="355" height="300"><param name="movie" value="http://togo.ebay.com/togo/togo.swf?2008013100" /><param name="flashvars" value="base=http://togo.ebay.com/togo/&lang=en-us&mode=search&query=(serial%2Crs232%2Crs-232)%20usb&pid=2840151" /><embed src="http://togo.ebay.com/togo/togo.swf?2008013100" type="application/x-shockwave-flash" width="355" height="300" flashvars="base=http://togo.ebay.com/togo/&lang=en-us&mode=search&query=(serial%2Crs232%2Crs-232)%20usb&pid=2840151"></embed></object> --><!--webbot
        bot="HTMLMarkup" endspan --></td>
    </tr>
</table>

<h2><a name="Multiple">Addressing and Multiple Wombats</a></h2>

<p>The Serial Wombat has the ability to add an additional 9th
byte to the beginning of each command packet. This allows more
than one Wombat to share a serial connection. This is achieved by
connecting all of the RX pins on the various Wombats together and
to the TX from the host or RS232 voltage converter chip logic
output. The Wombats' TX pins are connected to the input of a
&quot;logic AND&quot; chip. The output of the &quot;logic
AND&quot; is fed to the host, or to the RS232 voltage converter
chip logic input.</p>

<p>This scheme is possible in the PC to Wombat direction because
the transmissions from the PC go to all Wombats. However, if the
8 byte packet is not preceeded by the proper 8-bit address, then
the Wombat will ignore the message. Note that one can enable
addressing with only one Wombat in order to improve the
reliability of communication. If the host and Wombat get out of
sync then any packet which appears to start with the wrong
address will be ignored.</p>

<p>This scheme is possible in the Wombat to PC direction because
a Wombat will only speak immediately after spoken to. This
prevents the possibility of a bus collision, assuming that only
one Wombat assumes it's being spoken to at a time (due to
addressing). In order to prevent a physical voltage conflict, the
transmit outputs of all Wombats are fed into a logical AND chip.
The output of the AND is fed to the host, usually by means of a
voltage converter. An AND chip is used because the natural idle
state of a logic-level UART is high. Therefore, a
&quot;speaking&quot; Wombat will occasionally pull the line low,
while idle Wombats will remain high. Therefore, the desired
output from the &quot;speaking&quot; Wombat will propogate
through the AND chip. Should more than one Wombat attempt to
speak at a time, the result will likely be garbled.</p>

<p>In order to talk to multiple Wombats in an addressed manner it
is necessary for each Wombat to have a different address, and for
the host to know that address. A Wombat can be assigned an
address in a number of ways (See the Set System Parameter Address
message for details on how to do these):</p>

<ul>
    <li>Its address can be commanded over the serial port.
        However, this presents a problem. Simply sending a
        message such as &quot;Use address 57&quot; over the
        serial port would command all chips connected to that
        port to use address 57. Therefore, only one Wombat should
        be active when this command is issued. The easiest way to
        do this is to use a 10k pull up resistor for each
        Wombat's reset pin, then use a jumper to ground that pin
        on all Wombats but the one whose address is being set.
        This address can be stored in EEPROM for use at every
        power-up, so this only has to be done once.</li>
    <li>Its address can be determined by tying digital inputs
        high and low. Up to four pins can be specified to be read
        to generate an address from 0 to 15. In this way, for
        example, one Wombat may have pin 38 tied permanently
        high, and another Wombat has the same pin tied low. If
        both were simultatneously commanded to set their address
        based on pin 38, one would choose address &quot;1&quot;,
        and one would choose address &quot;0&quot;. Optionally,
        this address can be stored to EEPROM, so the Wombat will
        power up next time with that same address, even if those
        pins change.</li>
    <li>Its address can be determined by an A/D converstion (2
        bits). One Analog-Capable pin can be used to determine
        the Wombat's address, ranging from 0 to 3. For address
        zero, ground the pin. For address 1, connect the pin via
        a 3.6k 5% resistor to Vdd (your source voltage), and a
        6.2k 5% resistor to ground. For address 2, connect the
        pin via a 6.2k 5% resistor to Vdd and a 3.6k 5% resistor
        to ground. For address 3, connect the pin to Vdd.
        Optionally, this address can be stored to EEPROM, so the
        Wombat will power up next time with that same address,
        even the analog pin value changes in the future.</li>
    <li>Its address can be determined by an A/D converstion (4
        bits). One Analog-Capable pin can be used to determine
        the Wombat's address, ranging from 0 to 15. Use of a
        2-resistor voltage divider is recommended. The 4-bit A/D
        conversion is separate from the 2-bit because the use of
        two common 5% resistors can result in a variance of more
        than 1/16th of the output if you happen to get two
        reistors which are at the edges of their tollerance
        ranges. Therefore, 1% resistors are recommended for this
        purpose, or hand verify the value of 5% resistors before
        use. Optionally, this address can be stored to EEPROM, so
        the Wombat will power up next time with that same
        address, even the analog pin value changes in the
        future.Voltage division of Vdd for addresses:<br>
        <table border="0">
            <tr>
                <td>Address</td>
                <td>% of Vdd</td>
            </tr>
            <tr>
                <td>0</td>
                <td>0</td>
            </tr>
            <tr>
                <td align="right" width="64" height="17"
                style="height:12.75pt;width:48pt" x:num>1</td>
                <td align="right" width="64" style="width:48pt"
                x:num="9.375E-2" x:fmla="=A1/16 + 1/32">0.09375</td>
            </tr>
            <tr>
                <td align="right" height="17"
                style="height:12.75pt" x:num>2</td>
                <td align="right" x:num="0.15625"
                x:fmla="=A2/16 + 1/32">0.15625</td>
            </tr>
            <tr>
                <td align="right" height="17"
                style="height:12.75pt" x:num>3</td>
                <td align="right" x:num="0.21875"
                x:fmla="=A3/16 + 1/32">0.21875</td>
            </tr>
            <tr>
                <td align="right" height="17"
                style="height:12.75pt" x:num>4</td>
                <td align="right" x:num="0.28125"
                x:fmla="=A4/16 + 1/32">0.28125</td>
            </tr>
            <tr>
                <td align="right" height="17"
                style="height:12.75pt" x:num>5</td>
                <td align="right" x:num="0.34375"
                x:fmla="=A5/16 + 1/32">0.34375</td>
            </tr>
            <tr>
                <td align="right" height="17"
                style="height:12.75pt" x:num>6</td>
                <td align="right" x:num="0.40625"
                x:fmla="=A6/16 + 1/32">0.40625</td>
            </tr>
            <tr>
                <td align="right" height="17"
                style="height:12.75pt" x:num>7</td>
                <td align="right" x:num="0.46875"
                x:fmla="=A7/16 + 1/32">0.46875</td>
            </tr>
            <tr>
                <td align="right" height="17"
                style="height:12.75pt" x:num>8</td>
                <td align="right" x:num="0.53125"
                x:fmla="=A8/16 + 1/32">0.53125</td>
            </tr>
            <tr>
                <td align="right" height="17"
                style="height:12.75pt" x:num>9</td>
                <td align="right" x:num="0.59375"
                x:fmla="=A9/16 + 1/32">0.59375</td>
            </tr>
            <tr>
                <td align="right" height="17"
                style="height:12.75pt" x:num>10</td>
                <td align="right" x:num="0.65625"
                x:fmla="=A10/16 + 1/32">0.65625</td>
            </tr>
            <tr>
                <td align="right" height="17"
                style="height:12.75pt" x:num>11</td>
                <td align="right" x:num="0.71875"
                x:fmla="=A11/16 + 1/32">0.71875</td>
            </tr>
            <tr>
                <td align="right" height="17"
                style="height:12.75pt" x:num>12</td>
                <td align="right" x:num="0.78125"
                x:fmla="=A12/16 + 1/32">0.78125</td>
            </tr>
            <tr>
                <td align="right" height="17"
                style="height:12.75pt" x:num>13</td>
                <td align="right" x:num="0.84375"
                x:fmla="=A13/16 + 1/32">0.84375</td>
            </tr>
            <tr>
                <td align="right" height="17"
                style="height:12.75pt" x:num>14</td>
                <td align="right" x:num="0.90625"
                x:fmla="=A14/16 + 1/32">0.90625</td>
            </tr>
            <tr>
                <td align="right" height="17"
                style="height:12.75pt" x:num>15</td>
                <td align="right" x:num="0.96875"
                x:fmla="=A15/16 + 1/32">1</td>
            </tr>
        </table>
    </li>
</ul>

<p>Sometimes it may be desirable to send one command to all of
the Wombats on a bus. Any packet sent with an address of 0xFF
will be processed by all Wombats, but no Wombat will send a
response (because simultaneous responses would cause conflict on
the bus). </p>

<p>The character 'U' (0x55) will be discarded if received as the
address byte.</p>

<h2><a name="CommandTypes">Command Types</a></h2>

<p>Serial Wombat commands fall into two broad categories:</p>

<ul>
    <li>ASCII commands. These commands are designed to be typed
        into a terminal program such as Windows Hyperterminal.
        ASCII commands start with a command byte which
        corresponds to a typeable character. Numerical parameters
        are expressed as ASCII strings, rather than as packed
        binary numbers. Commands are case-sensitive in order to
        maximize the number of possible commands within the ASCII
        range. The command byte for ASCII commands is chosen to
        make the command as easy to remember as possible.</li>
    <li>Binary commands. These commands are designed to be sent
        by a program running on the host computer. The command
        byte numbers are 128 to 253. These correspond to
        non-ASCII characters. Binary commands typically take some
        number of 1 to 4 byte long parameters. Multi-byte
        parameters are sent most-significant byte first. Note
        that programs can use the ASCII commands as well as
        Binary commands. Binary commands are allocated command
        byte numbers in groups. For instance, queue related
        commands currently use commands 128 through 132.
        Additional commands will be left unassigned following
        number 132 in order to support future queue commands.</li>
</ul>

<h2><a name="ASCIICommands">ASCII Commands</a>:</h2>
<div align="left">

<table border="0" cellspacing="1">
    <tr>
        <td valign="top">Command/ASCII / Hexidecimal/ Decimal</td>
        <td valign="top" width="95%">Description</td>
    </tr>
    <tr>
        <td valign="top"><h3 align="left"><a name="Echo">Echo</a></h3>
        <p>'!'<br>
        0x21<br>
        33<br>
        </p>
        </td>
        <td valign="top" width="95%">This command will echo back
        to the host the same 8 byte packet when it is received.
        This command has no other effect on the system. This
        command is useful to verify that communication is
        possible between the host and the Wombat.<p>Example:</p>
        <table border="1">
            <tr>
                <td>Sent to the Wombat:</td>
                <td>'!'</td>
                <td>'A'</td>
                <td>'B'</td>
                <td>'C'</td>
                <td>'D'</td>
                <td>'E'</td>
                <td>'F'</td>
                <td>'G'</td>
            </tr>
            <tr>
                <td>Received by the Host:</td>
                <td>'!'</td>
                <td>'A'</td>
                <td>'B'</td>
                <td>'C'</td>
                <td>'D'</td>
                <td>'E'</td>
                <td>'F'</td>
                <td>'G'</td>
            </tr>
        </table>
        </td>
    </tr>
    <tr>
        <td valign="top"><h3><a name="ReadPublicDataBuffer">Read
        Public Data Buffer</a></h3>
        <p>'A'<br>
        0x41<br>
        65</p>
        </td>
        <td valign="top" width="95%">This command will return the
        public data for a channel given as an ascii string in the
        2nd and 3rd bytes. The command byte can be remembered
        with the neumonic &quot;A is the command to get the
        result of an <strong>A</strong>nalog conversion.&quot; If
        the 4th byte is 'H' then the result will be returned in
        hexadecimal with a leading X. If the 4th byte is not X
        then the value will be returned in decimal.<p>Example:</p>
        <p>Get the value of the public data provided by pin 4.
        Return that value in hexadecimal.</p>
        <table border="1" width="100%">
            <tr>
                <td valign="top">Data Sent to the Wombat:</td>
                <td valign="top" width="10%">'A'</td>
                <td valign="top" width="10%">'0'</td>
                <td valign="top" width="10%">'4'</td>
                <td valign="top" width="10%">'H'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="10%">Read Public Data
                buffer</td>
                <td valign="top" colspan="2" width="10%">Pin 4</td>
                <td valign="top" width="10%">Return value in
                hexadecimal</td>
                <td valign="top" colspan="4" width="10%">Unused</td>
            </tr>
            <tr>
                <td valign="top" colspan="9">&nbsp;</td>
            </tr>
            <tr>
                <td valign="top">Data Received by the host</td>
                <td valign="top" width="10%">'A'</td>
                <td valign="top" width="10%">'0'</td>
                <td valign="top" width="10%">'4'</td>
                <td valign="top" width="10%">'X'</td>
                <td valign="top" width="10%">'3'</td>
                <td valign="top" width="10%">'D'</td>
                <td valign="top" width="10%">'7'</td>
                <td valign="top" width="10%">'4'</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="10%">Read Public Data
                Buffer</td>
                <td valign="top" colspan="2" width="10%">Pin 4</td>
                <td valign="top" width="10%">Result is
                Hexadecimal</td>
                <td valign="top" colspan="4" width="10%">Some
                Hexidecimal Value Corresponding to the 16 bit
                value of pin 4's public data</td>
            </tr>
        </table>
        <p><br>
        </p>
        <p>Example:</p>
        <p>Get the value of the public data provided by pin 32.
        Return that value in decimall.</p>
        <table border="1" width="100%">
            <tr>
                <td>Data Sent to the Wombat:</td>
                <td valign="top" width="10%">'A'</td>
                <td valign="top" width="10%">'3'</td>
                <td valign="top" width="10%">'2'</td>
                <td valign="top" width="10%">'D'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
            </tr>
            <tr>
                <td>Meaning:</td>
                <td valign="top" width="10%">Read Public Data
                buffer</td>
                <td valign="top" colspan="2" width="10%">Pin 32</td>
                <td valign="top" width="10%">Return value in
                hexadecimal</td>
                <td valign="top" colspan="4" width="10%">Unused</td>
            </tr>
            <tr>
                <td colspan="9">&nbsp;</td>
            </tr>
            <tr>
                <td>Data Received by the host:</td>
                <td valign="top" width="10%">'A'</td>
                <td valign="top" width="10%">'3'</td>
                <td valign="top" width="10%">'2'</td>
                <td valign="top" width="10%">'4'</td>
                <td valign="top" width="10%">'3'</td>
                <td valign="top" width="10%">'1'</td>
                <td valign="top" width="10%">'2'</td>
                <td valign="top" width="10%">'7'</td>
            </tr>
            <tr>
                <td>Meaning:</td>
                <td valign="top" width="10%">Read Public Data
                Buffer</td>
                <td valign="top" colspan="2" width="10%">Pin 32</td>
                <td valign="top" colspan="5" width="10%">Some
                Hexidecimal Value Corresponding to the value of
                pin 32's public data. This 16 bit value may range
                from 0 to 65535.</td>
            </tr>
        </table>
        </td>
    </tr>
    <tr>
        <td valign="top"><h3><a name="SetBaudRate">Set Baud Rate</a></h3>
        <p>'B'<br>
        0x42<br>
        66</p>
        </td>
        <td valign="top" width="95%">This command will set a new
        communication Baud (or bits-per-second) rate for
        communication between the Serial Wombat and the host. No
        return message will be sent, in order to allow the host
        time after transmission to change baud rate. If the
        Autobaud Command is sent, then a 'U' (0x55) character
        MUST be the next character sent after this command and
        the host-side Baud Rate change. Failure to do so may
        cause communication to be permanently disrupted until the
        next Serial Wombat power-cycle. Other baud rate change
        commands do not require any additional action by the
        host.<p>If the 8th byte is 'E' then system will write to
        EEPROM to indicate that future powerups should use the
        new baud rate at powerup. If the 8th byte is not E then
        the powerup state will not be changed. Writing to EEPROM
        will suspend all other processing for up to 8 ms.</p>
        <p>Note that all baud rates are expressed as a 6
        character decimal number, with leading zeros as
        necessary.</p>
        <p>No action will be taken when a baud rate other than
        one of the following is used:</p>
        <p>Possible bps (Baud) values: 75, 110, 150, 300, 1200,
        2400, 4800, 9600, 19200, 38400, 57600, 115200.</p>
        <p>Note that aside from the Autobaud command, these
        values only work when the Wombat is operating from its
        internal clock source at the default frequency. Future
        versions of the Wombat software may allow the user to
        slow the clock down to conserve power, or to use an
        external clock source.</p>
        <table border="1" width="100%">
            <tr>
                <td valign="top">Data Sent to the Wombat:</td>
                <td valign="top" width="10%">'B'</td>
                <td valign="top" width="10%">'A'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'E'</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="10%">Set Baud Rate</td>
                <td valign="top" width="5%">Initiate Auto-baud. </td>
                <td valign="top" colspan="6" width="25%">Unused.
                This packet should be followed by at least one
                'U' character to initialize the baud rate. If the
                8th byte is 'E' then system will write to eeprom
                to indicate that future powerups should use
                Autobaud. If the 8th byte is not E then the
                powerup state will not be changed.</td>
            </tr>
        </table>
        <p><br>
        </p>
        <table border="1" width="100%">
            <tr>
                <td>Data Sent to the Wombat:</td>
                <td valign="top" width="10%">'B'</td>
                <td valign="top" width="10%">'0'</td>
                <td valign="top" width="10%">'0'</td>
                <td valign="top" width="10%">'0'</td>
                <td valign="top" width="10%">'0'</td>
                <td valign="top" width="10%">'7'</td>
                <td valign="top" width="10%">'5'</td>
                <td valign="top" width="10%">'U'</td>
            </tr>
            <tr>
                <td>Meaning:</td>
                <td valign="top" width="10%">Set Baud Rate</td>
                <td valign="top" colspan="6" width="28%">Set baud
                rate to 75 bps.</td>
                <td valign="top" width="2%">unused.</td>
            </tr>
        </table>
        <p><br>
        </p>
        </td>
    </tr>
    <tr>
        <td valign="top"><h3><a name="SendBinaryCommand">Send
        Binary Command</a> in ASCII</h3>
        <p>'C'<br>
        0x43<br>
        67</p>
        </td>
        <td valign="top" width="95%">This command is used to send
        a command from the binary portion of the command set
        using ascii based commands. Since binary commands are
        more information dense than ASCII commands, it takes four
        ASCII commands to send one binary command. This command
        is useful for testing using a terminal such as
        hyperterminal, since it allows a sequence of commands to
        be sent all at once. When sending commands using a stream
        of text from a file, it is recommended that 8 0x55
        characters ( ASCII 'U' ) be placed between each command
        to minimize corruption should any byte be dropped or
        misreceived.<p>The Wombat will echo back each of the four
        command packets, but will not send the response to the
        created binary command, as the response would also likely
        be in binary. Care should be taken that the commands are
        sent in order. The Wombat will act when a packet marked
        as fourth is received, even if a previous packet is
        missing.</p>
        <p>The second byte indicates the command number. Valid
        values are 0, 1, 2, and 3. The 3rd through 5th bytes of
        each ASCII command are the 1st, 3rd, 5th, or 7th binary
        command byte (depending on the command number), expressed
        as a three digit decimal number. The 6th through 8th
        bytes of each ASCII command 2nd, 4th, 6th, or 8th binary
        command byte (depending on the command number), expressed
        as a three digit number.</p>
        <p>Doing conversions by hand can be tedious and error
        prone. <a href="../../../../../cgi-bin/process_cmd.cgi">Use
        the script here!</a></p>
        </td>
    </tr>
    <tr>
        <td valign="top"><h3><a name="SetPin">Set Pin</a>
        Hardware Mode</h3>
        <p>'H'<br>
        0x48<br>
        72</p>
        </td>
        <td valign="top" width="95%">This command is used to
        configure the way a pin will behave when used as an
        analog output. A few pins have fixed behavior which
        cannot be changed:<br>
        <table border="0">
            <tr>
                <td>Pin 4</td>
                <td>&nbsp;</td>
                <td>16 level (4 bit) D/A converter</td>
            </tr>
            <tr>
                <td>Pin 16</td>
                <td>&nbsp;</td>
                <td>Hardware assisted PWM</td>
            </tr>
            <tr>
                <td>Pin 17</td>
                <td>&nbsp;</td>
                <td>Hardware assisted PWM</td>
            </tr>
        </table>
        <p>All other pins can be configured for the following
        modes:</p>
        <table border="0">
            <tr>
                <td>Setting</td>
                <td>&nbsp;</td>
                <td>Function</td>
            </tr>
            <tr>
                <td>1</td>
                <td>&nbsp;</td>
                <td>1-bit software PWM</td>
            </tr>
            <tr>
                <td>2</td>
                <td>&nbsp;</td>
                <td>2-bit software PWM</td>
            </tr>
            <tr>
                <td>3</td>
                <td>&nbsp;</td>
                <td>3-bit software PWM</td>
            </tr>
            <tr>
                <td>4</td>
                <td>&nbsp;</td>
                <td>4-bit software PWM</td>
            </tr>
            <tr>
                <td>5</td>
                <td>&nbsp;</td>
                <td>5-bit software PWM</td>
            </tr>
            <tr>
                <td>6</td>
                <td>&nbsp;</td>
                <td>6-bit software PWM</td>
            </tr>
            <tr>
                <td>7</td>
                <td>&nbsp;</td>
                <td>7-bit software PWM</td>
            </tr>
            <tr>
                <td>8</td>
                <td>&nbsp;</td>
                <td>Unused</td>
            </tr>
            <tr>
                <td>9</td>
                <td>&nbsp;</td>
                <td>MCP4821 12-bit D/A converter</td>
            </tr>
        </table>
        <p>Example:</p>
        <p>Set pin 19 to 5 bit software PWM.</p>
        <table border="1" width="100%">
            <tr>
                <td valign="top">Data Sent to the Wombat:</td>
                <td valign="top" width="10%">'H'</td>
                <td valign="top" width="10%">'1'</td>
                <td valign="top" width="10%">'9'</td>
                <td valign="top" width="10%">'0' </td>
                <td valign="top" width="10%">'5'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="10%">Set Pin Hardware
                Mode</td>
                <td valign="top" colspan="2" width="10%">Pin 20</td>
                <td valign="top" colspan="2" width="14%">Mode 05</td>
                <td valign="top" width="2%">&nbsp;</td>
                <td valign="top" width="2%">&nbsp;</td>
                <td valign="top" width="2%">&nbsp;</td>
            </tr>
        </table>
        </td>
    </tr>
    <tr>
        <td valign="top"><h3><a name="JumpToApp">Jump to App </a>From
        Bootloader</h3>
        <p>'J'<br>
        0x4A<br>
        74</p>
        </td>
        <td valign="top">This command is used to tell the Wombat
        that it should jump to the application on powerup (as
        opposed to staying in boot mode). This command is
        designed for use immediately after downloading a new
        firmware version using the boot mode.<p>Example:</p>
        <p>Jump to Application on powerup.</p>
        <table border="1" width="100%">
            <tr>
                <td valign="top">Data Sent to the Wombat:</td>
                <td valign="top" width="10%">'J'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="10%">Jump To App</td>
                <td valign="top" colspan="7" width="30%">Unused.</td>
            </tr>
        </table>
        </td>
    </tr>
    <tr>
        <td><h3>Lock Communications</h3>
        <p>'L'<br>
        0x4C<br>
        76</p>
        </td>
        <td valign="top">This command is designed to help the
        Wombat avoid executing unintended commands when operating
        over a datalink which may provide characters which are
        not commands. For instance, a typical Hayes compatible
        modem may send strings such as &quot;CONNECT 9600&quot;
        or &quot;RING&quot; which should not be interpreted by
        the Wombat. The Lock command allows the host (or the
        powerup sequence) to require a specific unlock command
        before other commands will be processed. The lock command
        consists of &quot;LOCK&quot; plus an additional 4 bytes
        provided by the host. Once locked, the Wombat will not
        respond to any command until the command &quot;Lock&quot;
        plus the same 4 bytes is sent (note the case difference,
        lower &quot;ock&quot; is for unlock). The lock and unlock
        commands must be properly framed, so it is recommended to
        send resync characters prior to locking or unlocking the
        Wombat.<p>Example:</p>
        <p>Lock the Wombat with the additional 4 bytes 0x01,
        0x02, 0x03 0x04</p>
        <table border="1" width="100%">
            <tr>
                <td valign="top">Data Sent to the Wombat:</td>
                <td valign="top" width="10%">'L'</td>
                <td valign="top" width="10%">'O'</td>
                <td valign="top" width="10%">'C'</td>
                <td valign="top" width="10%">'K'</td>
                <td valign="top" width="10%">0x01</td>
                <td valign="top" width="10%">0x02</td>
                <td valign="top" width="10%">0x03</td>
                <td valign="top" width="10%">0x04</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" colspan="4" width="24%">Lock the
                Wombat. Note upper case &quot;OCK&quot;</td>
                <td valign="top" width="4%">&nbsp;</td>
                <td valign="top" width="4%">&nbsp;</td>
                <td valign="top" width="4%">&nbsp;</td>
                <td valign="top" width="4%">&nbsp;</td>
            </tr>
        </table>
        <p>Example:</p>
        <p>UnLock the Wombat with the additional 4 bytes 0x01,
        0x02, 0x03 0x04</p>
        <table border="1" width="100%">
            <tr>
                <td valign="top">Data Sent to the Wombat:</td>
                <td valign="top" width="10%">'L'</td>
                <td valign="top" width="10%">'o'</td>
                <td valign="top" width="10%">'c'</td>
                <td valign="top" width="10%">'k'</td>
                <td valign="top" width="10%">0x01</td>
                <td valign="top" width="10%">0x02</td>
                <td valign="top" width="10%">0x03</td>
                <td valign="top" width="10%">0x04</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" colspan="4" width="24%">UnLock
                the Wombat. Note lower case &quot;ock&quot;</td>
                <td valign="top" colspan="4" width="16%">Same 4
                bytes as lock command</td>
            </tr>
        </table>
        </td>
    </tr>
    <tr>
        <td valign="top"><h3><a name="SetPin">Set Pin</a> to
        High, Low, or Input</h3>
        <p>'P'<br>
        0x50<br>
        80</p>
        </td>
        <td valign="top" width="95%">This command is used to set
        the state of one to five consecutively numbered pins.
        Each Pin may be set to high, low, input, or left
        unchanged. The 2nd and 3rd bytes are the pin number of
        the first pin to be set, in ASCII. The 4th byte contains
        the state to which the specified pin should be set: '0'
        (ascii zero) for low, 1 for high, or I for input. Any
        other value will leave the pin unchanged. Similarly, the
        5th byte will change the next pin if 0,1, or I is given.
        Otherwise, the next pin will stay unchanged. The
        remaining three bytes will change the next three pins. Is
        is suggested to use 'U', the resync value, for unused
        pins.<p>Example:</p>
        <p>Set pin 20 to output high.</p>
        <table border="1" width="100%">
            <tr>
                <td valign="top">Data Sent to the Wombat:</td>
                <td valign="top" width="10%">'P'</td>
                <td valign="top" width="10%">'2'</td>
                <td valign="top" width="10%">'0'</td>
                <td valign="top" width="10%">'1' </td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="10%">Set Pins</td>
                <td valign="top" colspan="2" width="10%">Pin 20</td>
                <td valign="top" width="10%">Set Pin 20 high</td>
                <td valign="top" colspan="4" width="10%">Leave
                pins 21, 22, 23, and 24 unchanged.</td>
            </tr>
        </table>
        <p><br>
        Example:</p>
        <p>Set pin 13 to output low, pin 15 to output high, and
        pin 16 to input.</p>
        <table border="1" width="100%">
            <tr>
                <td valign="top">Data Sent to the Wombat:</td>
                <td valign="top" width="10%">'P'</td>
                <td valign="top" width="10%">'1'</td>
                <td valign="top" width="10%">'3'</td>
                <td valign="top" width="10%">'0' </td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'1'</td>
                <td valign="top" width="10%">'I'</td>
                <td valign="top" width="10%">'U'</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="10%">Set Pins</td>
                <td valign="top" colspan="2" width="10%">Pin 13</td>
                <td valign="top" width="10%">Set pin 13 low</td>
                <td valign="top" width="4%">Leave Pin 14
                unchanged</td>
                <td valign="top" width="2%">Set pin 15 high</td>
                <td valign="top" width="2%">Set pin 16 to Input</td>
                <td valign="top" width="2%">Leave pin 17
                unchanged.</td>
            </tr>
        </table>
        </td>
    </tr>
    <tr>
        <td valign="top"><h3><a name="SetPublicData">Set Public
        Data</a></h3>
        <p>'S'<br>
        0x53<br>
        83</p>
        </td>
        <td valign="top">Set a pin's public data. This is used
        for certain pin modes such as Servo Control which act on
        their own public data. Values are expressed in ASCII
        decimal. The first two bytes after 'S' are the pin number
        (numbers less than 10 start with a zero). The final 5
        bytes are a 16-bit value, right justified. Leading digits
        should be filled with zero.<p>Example:</p>
        <p>Set pin 19's public data to 375 decimal.</p>
        <table border="1" width="100%">
            <tr>
                <td valign="top">Data Sent to the Wombat:</td>
                <td valign="top" width="10%">'S'</td>
                <td valign="top" width="10%">'1'</td>
                <td valign="top" width="10%">'9'</td>
                <td valign="top" width="10%">'0' </td>
                <td valign="top" width="10%">'0'</td>
                <td valign="top" width="10%">'3'</td>
                <td valign="top" width="10%">'5'</td>
                <td valign="top" width="10%">'5'</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="10%">Set Pin Public Data</td>
                <td valign="top" colspan="2" width="10%">Pin 19</td>
                <td valign="top" colspan="5" width="20%">355 (A
                16-bit number, expressed in ASCII in decimal with
                leading zeros).</td>
            </tr>
        </table>
        </td>
    </tr>
    <tr>
        <td valign="top"><h3><a name="WriteToEEPROM">Write To
        EEPROM</a></h3>
        <p>'e'<br>
        0x65<br>
        101</p>
        </td>
        <td valign="top" width="95%">This command is used to
        write a single byte into EEPROM. The Serial Wombat has
        1024 bytes of EEPROM, of which addresses 512 to 1023
        (addresses start at 0) are allocated for use by the host
        in the User EEPROM Area. Additionally, the address 511 is
        used to indicate how many custom powerup initialization
        messages are stored in EEPROM.<p>This command takes a
        four character, 16-bit address between 0x01FF and 0x03FF
        (511 to 1023 decimal) expressed in hexidecimal and a two
        character, 8-bit piece of data expressed in hexadecimal
        to store in EEPROM. The 8th byte is unused and should be
        set to the resync character (0x55).</p>
        <p>Note that all processing stops during EEPROM
        programming, which may take up to 4 milliseconds under
        some voltage and temperature conditions. During this time
        no pin-processing will take place, and no communications
        will be acknowledged. Therefore, if the user is going to
        stream a number of these commands from a file, it is
        recommended that enough resync characters be included
        between messages to take 4ms to transmit. At 9600 Baud
        this would be approximately 4 characters.</p>
        <p>The Wombat returns An echo of the first 5 bytes,
        followed by the value read from EEPROM after programming,
        and an echo of the 8th byte. Unless some error occurs
        this value should match the value sent. A communicatons
        error message will be returned if the address to program
        is not between 511 and 1023.</p>
        <p>Example:</p>
        <p>Program EEPROM location 742 to value 0x3D</p>
        <table border="1" width="100%">
            <tr>
                <td valign="top">Data Sent to the Wombat:</td>
                <td valign="top" width="10%">'e'</td>
                <td valign="top" width="10%">'0'</td>
                <td valign="top" width="10%">'2'</td>
                <td valign="top" width="10%">'E' </td>
                <td valign="top" width="10%">'6'</td>
                <td valign="top" width="10%">'3'</td>
                <td valign="top" width="10%">'D'</td>
                <td valign="top" width="10%">'U'</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="10%">Set Pins</td>
                <td valign="top" colspan="4" width="24%">Address
                742 expressed in hex is 0x02E6</td>
                <td valign="top" colspan="2" width="4%">Write
                Value 0x3D</td>
                <td valign="top" width="2%">Unused.</td>
            </tr>
        </table>
        <p><br>
        </p>
        </td>
    </tr>
    <tr>
        <td valign="top"><h3><a name="ReadFromEEPROM">Read From
        EEPROM</a></h3>
        <p>'r'<br>
        0x72<br>
        114</p>
        </td>
        <td valign="top" width="95%">This command is used to read
        a single byte from EEPROM. The Serial Wombat has 1024
        bytes of EEPROM, of which addresses 512 to 1023
        (addresses start at 0) are allocated for use by the host
        in the User EEPROM Area. Additionally, the address 511 is
        used to indicate how many custom powerup initialization
        messages are stored in EEPROM.<p>This command takes a
        four character, 16-bit address between 0x0000 and 0x03FF
        (0 to 1023 decimal) expressed in hexidecimal. The
        remaining three bytes should be set to the resync
        character (0x55). The 1st through 5th bytes are echoed
        back to the user. The value of the given EEPROM Location
        is returned in the 6th and 7th byte. The 8th byte is an
        echo of the 8th and unused byte of the command sent to
        the Wombat.</p>
        <p>Example:</p>
        <p>Read EEPROM location 742</p>
        <table border="1" width="100%">
            <tr>
                <td>Data Sent to the Wombat:</td>
                <td valign="top" width="10%">'r'</td>
                <td valign="top" width="10%">'0'</td>
                <td valign="top" width="10%">'2'</td>
                <td valign="top" width="10%">'E'</td>
                <td valign="top" width="10%">'6'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
            </tr>
            <tr>
                <td>Meaning:</td>
                <td valign="top" width="10%">Read EEPROM Location</td>
                <td valign="top" colspan="4" width="24%">Address
                742 expressed in Hexidecimal</td>
                <td valign="top" colspan="3" width="6%">Unused</td>
            </tr>
            <tr>
                <td colspan="9">&nbsp;</td>
            </tr>
            <tr>
                <td>Data Received by the host:</td>
                <td valign="top" width="10%">'r'</td>
                <td valign="top" width="10%">'3'</td>
                <td valign="top" width="10%">'2'</td>
                <td valign="top" width="10%">'4'</td>
                <td valign="top" width="10%">'3'</td>
                <td valign="top" width="10%">'3'</td>
                <td valign="top" width="10%">'D'</td>
                <td valign="top" width="10%">'U'</td>
            </tr>
            <tr>
                <td>Meaning:</td>
                <td valign="top" width="10%">Read EEPROM Location</td>
                <td valign="top" colspan="4" width="14%">Address
                742 expressed in Hexidecimal</td>
                <td valign="top" colspan="2" width="4%">Value in
                address 742 is 0x3D (example. Real value will
                vary)</td>
                <td valign="top" width="2%">Echo of 8th byte sent
                to Wombat</td>
            </tr>
        </table>
        <p><br>
        </p>
        </td>
    </tr>
    <tr>
        <td valign="top"><h3><a name="GetFirmwareVersion">Get
        Firmware Version</a></h3>
        <p>'V'<br>
        0x56<br>
        86</p>
        </td>
        <td valign="top" width="95%">This command is used to read
        the version of firmware loaded into the Wombat. It will
        return a string which starts with &quot;VW&quot; followed
        by 3 sets of two digits, representing the major, minor,
        and revision levels of the currently loaded firmware.
        This command is present in versions starting with
        WV010200, or 1_2_0.<table border="1" width="100%">
            <tr>
                <td>Data Sent to the Wombat:</td>
                <td valign="top" width="10%">'V'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
                <td valign="top" width="10%">'U'</td>
            </tr>
            <tr>
                <td>Meaning:</td>
                <td valign="top" width="10%">Get Version</td>
                <td valign="top" width="6%">Unused</td>
                <td valign="top" width="6%">Unused</td>
                <td valign="top" width="6%">Unused</td>
                <td valign="top" width="6%">Unused</td>
                <td valign="top" width="2%">Unused</td>
                <td valign="top" width="2%">Unused</td>
                <td valign="top" width="2%">Unused</td>
            </tr>
            <tr>
                <td colspan="9">&nbsp;</td>
            </tr>
        </table>
        </td>
    </tr>
</table>
</div>

<h2 align="left"><a name="BinaryCommands">Binary Commands</a></h2>
<div align="left">

<table border="0" cellspacing="1">
    <tr>
        <td valign="top" 2">Command<p>Hexidecimal/ Decimal</p>
        </td>
        <td align="center" valign="top" width="95%">Description</td>
    </tr>
    <tr>
        <td valign="top" 2"><h3 align="left"><a
        name="InitializeRamQueue">Initialize Ram Queue</a></h3>
        <p>0x80<br>
        128<br>
        </p>
        </td>
        <td valign="top" width="95%">This command will create a
        ram queue in the User RAM area at the given address. The
        2nd and 3rd bytes hold the address of the queue. The 4th
        and 5th bytes hold the size of the queue. The size sent
        is the number of bytes in the queue, not the number of
        bytes taken up by the queue plus its internal-use header.
        The 6th byte contains the queue type. Set this byte to
        zero, as only standard queues are currently supported.
        Future queue types may support optimizations for
        run-length encoding of queue data, data sizes of other
        than 8 bits, or support for off-board RAM or EEPROM. The
        7th and 8th bytes are unused for a standard queue
        initialization and should be set to the resync character.
        A communications error message will result if the queue
        cannot be created. <p>If successful this command sets the
        last host modified address parameter to the address of
        the created queue.</p>
        <p>Example:</p>
        <p>Create a queue of size 350 bytes at address 0x0020:</p>
        <table border="1" width="100%">
            <tr>
                <td valign="top">Data Sent to the Wombat:</td>
                <td valign="top" width="10%">0x80</td>
                <td valign="top" width="10%">0x00</td>
                <td valign="top" width="10%">0x20</td>
                <td valign="top" width="10%">0x01</td>
                <td valign="top" width="10%">0x5E</td>
                <td valign="top" width="10%">0x00</td>
                <td valign="top" width="10%">0x55</td>
                <td valign="top" width="10%">0x55</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="10%">Initialize Queue</td>
                <td valign="top" colspan="2" width="12%">Address
                0x0020</td>
                <td valign="top" colspan="2" width="12%">Size 350
                bytes (0x015E in hexadecimal)</td>
                <td valign="top" width="2%">Standard Queue</td>
                <td valign="top" colspan="2" width="4%">Unused.</td>
            </tr>
        </table>
        </td>
    </tr>
    <tr>
        <td valign="top" 2"><h3><a name="GetQueueInfo">Get Queue
        Info</a></h3>
        <p>0x81<br>
        129</p>
        </td>
        <td valign="top" width="95%">This command returns the
        status of a previously created queue. The 2nd and 3rd
        bytes are the address of the queue to be queried. The 4th
        through 8th bytes are unused and should be set to the
        resync character.<p>The Wombat will respond with the
        queue info. The 2nd and 3rd bytes contain the allocated
        size of the queue. The 4th and 5th bytes contain the
        number of bytes currently used in the queue. The 6th and
        7th bytes contain the size of the user data area. The 8th
        byte is unused and will match 8th byte transmitted to the
        Wombat.</p>
        <p>Example:</p>
        <p>Query the status of the queue created in the
        Initialize Ram Queue example above. Assume that the queue
        currently has 258 items in it.</p>
        <table border="1" width="100%">
            <tr>
                <td>Data Sent to the Wombat:</td>
                <td valign="top" width="10%">0x81</td>
                <td valign="top" width="10%">0x00</td>
                <td valign="top" width="10%">0x20</td>
                <td valign="top" width="10%">0x55</td>
                <td valign="top" width="10%">0x55</td>
                <td valign="top" width="10%">0x55</td>
                <td valign="top" width="10%">0x55</td>
                <td valign="top" width="10%">0x55</td>
            </tr>
            <tr>
                <td>Meaning:</td>
                <td valign="top" width="5%">Get Queue Info</td>
                <td valign="top" colspan="2" width="10%">Queue
                Address 0x0020</td>
                <td valign="top" colspan="5" width="25%">Unused</td>
            </tr>
            <tr>
                <td colspan="9">&nbsp;</td>
            </tr>
            <tr>
                <td>Data Received by the host:</td>
                <td valign="top" width="10%">0x81</td>
                <td valign="top" width="10%">0x01</td>
                <td valign="top" width="10%">0x5E</td>
                <td valign="top" width="10%">0x01</td>
                <td valign="top" width="10%">0x02</td>
                <td valign="top" width="10%">0x02</td>
                <td valign="top" width="10%">0xA4</td>
                <td valign="top" width="10%">0x55</td>
            </tr>
            <tr>
                <td>Meaning:</td>
                <td valign="top" width="10%">Get Queue Info</td>
                <td valign="top" colspan="2" width="8%">Queue
                Size is 350 bytes (constant once queue is
                initalized)</td>
                <td valign="top" colspan="2" width="6%">The queue
                currently contains 258 bytes (varies as data is
                added and removed from queue)</td>
                <td valign="top" colspan="2" width="4%">The user
                data area is 676 bytes long (constant for any
                release of the Wombat)</td>
                <td valign="top" width="2%">Echo of 8th byte sent
                to Wombat</td>
            </tr>
        </table>
        <p><br>
        </p>
        </td>
    </tr>
    <tr>
        <td valign="top" 2"><h3><a name="GetQueueData">Get Queue
        Data</a></h3>
        <p>0x82<br>
        130</p>
        </td>
        <td valign="top" width="95%">This command is used to move
        data from a Wombat Queue to the Host. The host sends a
        message containing the address of the queue and the
        number of bytes requested. The host may request up to 6
        bytes per message. If more than 6 bytes are requested, or
        if the queue is not valid, then a communications error
        message will be returned. The 2nd and 3rd byte contain
        the address of the queue to be accessed. The 4th byte
        contains the maximum number of bytes to be gotten from
        the queue. The 5th through 8th bytes are unused, and
        should be set to the resync character. Note that no error
        will be returned if this command is issued against a
        valid but empty queue.<p>The Wombat will return a packet.
        The 2nd byte will indicate how many bytes were removed
        from the queue. The 3rd through 8th bytes will contain
        the removed data. The first byte removed from the queue
        will be placed in the 3rd byte of the response message.</p>
        <p>If successful this command sets the last host modified
        address parameter to the address of the queue. A return
        of 0 bytes from a vaild but empty queue will set the last
        host modified queue parameter to the address of the
        queue.</p>
        <p>Example:</p>
        <p>Query the status of the queue created in the
        Initialize Ram Queue example above. Assume that the queue
        currently has 4 items in it: 0x23, 0x47, 0xAF, and 0xC0.</p>
        <table border="1" width="100%">
            <tr>
                <td>Data Sent to the Wombat:</td>
                <td valign="top" width="10%">0x82</td>
                <td valign="top" width="10%">0x00</td>
                <td valign="top" width="10%">0x20</td>
                <td valign="top" width="10%">0x06</td>
                <td valign="top" width="10%">0x55</td>
                <td valign="top" width="10%">0x55</td>
                <td valign="top" width="10%">0x55</td>
                <td valign="top" width="10%">0x55</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="5%">Get Queue Data</td>
                <td valign="top" colspan="2" width="10%">Queue
                Address 0x0020</td>
                <td valign="top" width="5%">Retreive up to 6
                bytes from queue</td>
                <td valign="top" colspan="4" width="20%">Unused. </td>
            </tr>
            <tr>
                <td colspan="9">&nbsp;</td>
            </tr>
            <tr>
                <td>Data Received by the host:</td>
                <td valign="top" width="10%">0x82</td>
                <td valign="top" width="10%">0x04</td>
                <td valign="top" width="10%">0x23</td>
                <td valign="top" width="10%">0x47</td>
                <td valign="top" width="10%">0xAF</td>
                <td valign="top" width="10%">0xC0</td>
                <td valign="top" width="10%">0x55</td>
                <td valign="top" width="10%">0x55</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="10%">Get Queue Data</td>
                <td valign="top" width="4%">Four bytes were
                removed from the queue.</td>
                <td valign="top" width="4%">First Byte Removed
                from queue</td>
                <td valign="top" width="3%">Second Byte Removed
                from queue</td>
                <td valign="top" width="3%">Third Byte Removed
                from queue</td>
                <td valign="top" width="2%">Fourth Byte Removed
                from queue</td>
                <td valign="top" width="2%">Not used since only 4
                bytes removed</td>
                <td valign="top" width="2%">Not used since only 4
                bytes removed</td>
            </tr>
        </table>
        </td>
    </tr>
    <tr>
        <td valign="top"><h3><a name="PutQueueData">Put Queue
        Data</a></h3>
        <p>0x83<br>
        131</p>
        </td>
        <td valign="top" width="95%">The Put Queue Data command
        is used to move data from the Host to a Wombat Queue.
        This command can be used to send up to four bytes of data
        to the Wombat. The message contains the address of the
        queue into which the data will be placed, the number of
        bytes to place (0 to 4) and the data to be placed in the
        queue. An communications error message will be returned
        if the queue is not valid, or if there is not enough
        space in the queue to place the requested number of
        bytes.<p>If successful this command sets the last host
        modified queue parameter to the address of the queue. </p>
        <p>Upon success, the Wombat will echo the first four
        bytes of the message. The 5th and 6th byte will contain
        the size of the queue. The 7th and 8th bytes will contain
        the number of bytes in the queue following the insertion
        of the sent data.</p>
        <p>Example: Place 3 bytes, 0x11, 0x00, and 0xEC into the
        queue created in the Initialize Ram Queue example above.
        Assume that 271 bytes of data are in the queue before
        this message.</p>
        <table border="1" width="100%">
            <tr>
                <td>Data Sent to the Wombat:</td>
                <td valign="top" width="10%">0x83</td>
                <td valign="top" width="10%">0x00</td>
                <td valign="top" width="10%">0x20</td>
                <td valign="top" width="10%">0x03</td>
                <td valign="top" width="10%">0x11</td>
                <td valign="top" width="10%">0x00</td>
                <td valign="top" width="10%">0xEC</td>
                <td valign="top" width="10%">0x55</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="5%">Put Queue Data</td>
                <td valign="top" colspan="2" width="10%">Queue
                Address 0x0020</td>
                <td valign="top" width="5%">Put 3 bytes in queue</td>
                <td valign="top" width="5%">Data</td>
                <td valign="top" width="5%">Data</td>
                <td valign="top" width="5%">Data</td>
                <td valign="top" width="5%">Unused in this
                example</td>
            </tr>
            <tr>
                <td colspan="9">&nbsp;</td>
            </tr>
            <tr>
                <td>Data Received by the host:</td>
                <td valign="top" width="10%">0x83</td>
                <td valign="top" width="10%">0x00</td>
                <td valign="top" width="10%">0x20</td>
                <td valign="top" width="10%">0x03</td>
                <td valign="top" width="10%">0x01</td>
                <td valign="top" width="10%">0x5E</td>
                <td valign="top" width="10%">0x01</td>
                <td valign="top" width="10%">0x12</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="10%">Put Queue Data</td>
                <td valign="top" colspan="2" width="8%">Queue
                Address 0x0020</td>
                <td valign="top" width="3%">3 bytes added to
                queue</td>
                <td valign="top" colspan="2" width="5%">Queue
                size is 350 bytes</td>
                <td valign="top" colspan="2" width="4%">274 bytes
                are now in the queue</td>
            </tr>
        </table>
        </td>
    </tr>
    <tr>
        <td valign="top"><h3><a name="QueueSevenBytes">Queue
        Seven Bytes</a></h3>
        <p align="left">0x84<br>
        132</p>
        </td>
        <td valign="top" width="95%">The Queue Seven Bytes
        command is designed to immediately follow the Put Queue
        Data command when many bytes need to be added to a queue.
        This command will place the 2nd through 8th bytes into
        the queue indicated by the last host modified queue
        parameter. This parameter is set by any command which
        modifies a queue. <p>The Wombat will respond with a
        message which has the address of the modified queue in
        the 2nd and 3rd bytes, 0x07 in the fourth byte, the queue
        size in the 5th and 6th bytes. The 7th and 8th bytes will
        contain the number of bytes in the queue following the
        insertion of the sent data. </p>
        <p>An communications error message will be sent if the
        last host modified address parameter points to an invalid
        queue, or if there are not 7 bytes of available space in
        the queue.</p>
        <p>Example: Place 7 bytes, 0x21, 0x14, 0xFC, 0x3D, 0x05,
        0x12, and 0x78 into the queue created used in Put queue
        data example above. Assume this command is issued
        immediately after that example.</p>
        <table border="1" width="100%">
            <tr>
                <td>Data Sent to the Wombat:</td>
                <td valign="top" width="10%">0x84</td>
                <td valign="top" width="10%">0x21</td>
                <td valign="top" width="10%">0x14</td>
                <td valign="top" width="10%">0xFC</td>
                <td valign="top" width="10%">0x3D</td>
                <td valign="top" width="10%">0x05</td>
                <td valign="top" width="10%">0x12</td>
                <td valign="top" width="10%">0x78</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="5%">Queue Seven Bytes</td>
                <td valign="top" width="5%">Data</td>
                <td valign="top" width="5%">Data</td>
                <td valign="top" width="5%">Data</td>
                <td valign="top" width="5%">Data</td>
                <td valign="top" width="5%">Data</td>
                <td valign="top" width="5%">Data</td>
                <td valign="top" width="5%">Data</td>
            </tr>
            <tr>
                <td colspan="9">&nbsp;</td>
            </tr>
            <tr>
                <td>Data Received by the host:</td>
                <td valign="top" width="10%">0x83</td>
                <td valign="top" width="10%">0x00</td>
                <td valign="top" width="10%">0x20</td>
                <td valign="top" width="10%">0x07</td>
                <td valign="top" width="10%">0x01</td>
                <td valign="top" width="10%">0x5E</td>
                <td valign="top" width="10%">0x01</td>
                <td valign="top" width="10%">0x19</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="10%">Queue Seven Bytes</td>
                <td valign="top" colspan="2" width="8%">Queue
                Address 0x0020</td>
                <td valign="top" width="3%">3 bytes added to
                queue</td>
                <td valign="top" colspan="2" width="5%">Queue
                size is 350 bytes</td>
                <td valign="top" colspan="2" width="4%">281 bytes
                are now in the queue</td>
            </tr>
        </table>
        </td>
    </tr>
    <tr>
        <td valign="top"><h3><a name="SetUserRam">Set User RAM</a></h3>
        <p align="left">0x92<br>
        146</p>
        </td>
        <td valign="top" width="95%">The Set User RAM command
        allows the user to place data into the User RAM area for
        use by various pin modes. 0 to 4 bytes can be written.
        The first byte of this message is 146. The next two bytes
        represent the address in user RAM where the first data
        byte is to be stored. The fourth byte is the number of
        data bytes to write, and the 5th through 8th bytes are
        data. The packet must always be 8 bytes long. Set unused
        bytes to 0x55. The sent message is echoed by the Wombat.<p>This
        command sets the last host modified address to the next
        address after those which were written.</p>
        <p>Example: Write the string &quot;JonB&quot; to address
        302 in user memory.</p>
        <table border="1" width="100%">
            <tr>
                <td>Data Sent to the Wombat:</td>
                <td valign="top" width="10%">0x92</td>
                <td valign="top" width="10%">0x01</td>
                <td valign="top" width="10%">0x2E</td>
                <td valign="top" width="10%">4</td>
                <td valign="top" width="10%">74</td>
                <td valign="top" width="10%">111</td>
                <td valign="top" width="10%">110</td>
                <td valign="top" width="10%">66</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="5%">Set User Ram</td>
                <td valign="top" colspan="2" width="10%">Address
                302 represented in hex is 0x12E</td>
                <td valign="top" width="5%">4 bytes of data
                follow</td>
                <td valign="top" width="5%">Ascii 'J' is 74</td>
                <td valign="top" width="5%">Ascii 'o' is 111</td>
                <td valign="top" width="5%">Ascii 'n' is 110</td>
                <td valign="top" width="5%">Ascii 'B' is<p>66</p>
                </td>
            </tr>
        </table>
        </td>
    </tr>
    <tr>
        <td valign="top"><h3><a name="Set7BytesofUserRAM">Set 7
        Bytes of User RAM</a></h3>
        <p align="left">0x93<br>
        147</p>
        </td>
        <td valign="top" width="95%">This command is designed to
        increase efficiency when moving data into User RAM. After
        the user has sent up to 4 bytes using the <a
        href="#SetUserRAM">Set User RAM</a> command, addtional
        sets of 7 bytes can be sent to the immediately following
        addresses in User RAM. The first byte is 0x93. The seven
        following bytes are data bytes to be written to RAM,
        starting at the last host modified address.<p>This
        command sets the last host modified address to the next
        address after those which were written.</p>
        <p>See the next command for an example.</p>
        </td>
    </tr>
    <tr>
        <td valign="top"><h3><a name="SetXBytesofUserRAM">Set X
        Bytes of User RAM</a></h3>
        <p align="left">0x94<br>
        148</p>
        </td>
        <td valign="top" width="95%">This command is designed to
        complete user RAM settings using the <a
        href="#SetUserRAM">Set User RAM</a> and <a
        href="#Set7BytesofUserRAM">Set 7 Bytes of User RAM</a>
        commands. Up to 6 bytes can be sent to the immediately
        following addresses in User RAM. The first byte is 0x94.
        The second byte is the number of data bytes that follow.
        The six following bytes are data bytes to be written to
        RAM, starting at the last host modified address. This
        packet must always be 8 bytes long. Unused bytes should
        be set to 0x55.<p>This command sets the last host
        modified address to the next address after those which
        were written.</p>
        <p>Example: Place the string &quot;Serial Wombat
        Rocks!!!&quot; in User Ram starting at at address 0x100</p>
        <p>Set the address and send the first four bytes with the
        Set User RAM command:</p>
        <table border="1" width="100%">
            <tr>
                <td>Data Sent to the Wombat:</td>
                <td valign="top" width="10%">0x92</td>
                <td valign="top" width="10%">0x01</td>
                <td valign="top" width="10%">0x00</td>
                <td valign="top" width="10%">4</td>
                <td valign="top" width="10%">83</td>
                <td valign="top" width="10%">101</td>
                <td valign="top" width="10%">114</td>
                <td valign="top" width="10%">105</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="5%">Set User Ram</td>
                <td valign="top" colspan="2" width="10%">Address
                0x100</td>
                <td valign="top" width="5%">4 bytes of data
                follow</td>
                <td valign="top" width="5%">Ascii 'S' is 83</td>
                <td valign="top" width="5%">Ascii 'e' is 101</td>
                <td valign="top" width="5%">Ascii 'r' is 114</td>
                <td valign="top" width="5%">Ascii 'i' is 105</td>
            </tr>
        </table>
        <p>Send as many bytes as possible using the Set 7 Bytes
        of User RAM Command:</p>
        <table border="1" width="100%">
            <tr>
                <td>Data Sent to the Wombat:</td>
                <td valign="top" width="10%">0x93</td>
                <td valign="top" width="10%">97</td>
                <td valign="top" width="10%">108</td>
                <td valign="top" width="10%">32</td>
                <td valign="top" width="10%">87</td>
                <td valign="top" width="10%">119</td>
                <td valign="top" width="10%">109</td>
                <td valign="top" width="10%">98</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="5%">Set 7 Bytes of User
                Ram</td>
                <td valign="top" width="5%">Ascii 'a' is 97</td>
                <td valign="top" width="5%">Ascii 'l' is 108</td>
                <td valign="top" width="5%">Ascii ' ' is 32</td>
                <td valign="top" width="5%">Ascii 'W' is 87</td>
                <td valign="top" width="5%">Ascii 'o' is 111</td>
                <td valign="top" width="5%">Ascii 'm' is 109</td>
                <td valign="top" width="5%">Ascii 'b' is 98</td>
            </tr>
        </table>
        <table border="1" width="100%">
            <tr>
                <td>Data Sent to the Wombat:</td>
                <td valign="top" width="10%">0x93</td>
                <td valign="top" width="10%">97</td>
                <td valign="top" width="10%">116</td>
                <td valign="top" width="10%">32</td>
                <td valign="top" width="10%">82</td>
                <td valign="top" width="10%">111</td>
                <td valign="top" width="10%">99</td>
                <td valign="top" width="10%">107</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="5%">Set 7 Bytes of User
                Ram</td>
                <td valign="top" width="5%">Ascii 'a' is 97</td>
                <td valign="top" width="5%">Ascii 't' is 116</td>
                <td valign="top" width="5%">Ascii ' ' is 32</td>
                <td valign="top" width="5%">Ascii 'R' is 82</td>
                <td valign="top" width="5%">Ascii 'o' is 111</td>
                <td valign="top" width="5%">Ascii 'c' is 99</td>
                <td valign="top" width="5%">Ascii 'k' is 107</td>
            </tr>
        </table>
        <p>Send remaining bytes using the Set X Bytes of User Ram
        Command:</p>
        <table border="1" width="100%">
            <tr>
                <td>Data Sent to the Wombat:</td>
                <td valign="top" width="10%">0x94</td>
                <td valign="top" width="10%">4</td>
                <td valign="top" width="10%">115</td>
                <td valign="top" width="10%">33</td>
                <td valign="top" width="10%">33</td>
                <td valign="top" width="10%">33</td>
                <td valign="top" width="10%">0x55</td>
                <td valign="top" width="10%">0x55</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="5%">Set X Bytes of User
                Ram</td>
                <td valign="top" width="5%">4 bytes follow</td>
                <td valign="top" width="5%">Ascii 's' is 115</td>
                <td valign="top" width="5%">Ascii '!' is 33</td>
                <td valign="top" width="5%">Ascii '!' is 33</td>
                <td valign="top" width="5%">Ascii '!' is 33</td>
                <td valign="top" width="5%">Unused</td>
                <td valign="top" width="5%">Unused</td>
            </tr>
        </table>
        </td>
    </tr>
    <tr>
        <td valign="top"><h3><a name="GetSystemInfo">Get System
        Info</a></h3>
        <p>0x96<br>
        150</p>
        </td>
        <td valign="top" width="95%">This command is used to get
        various information from the Serial Wombat. The 2nd byte
        of this command specifies what information is to be
        retrieved. The 3rd through 8th bytes are unused.<p>The
        following table gives the information provided by each
        information identification number. The first byte of the
        return message is the Get System Info command number,
        0x96. All multibyte values are transmitted
        most-significant byte first.</p>
        <table border="1">
            <tr>
                <td valign="top">Information<br>
                Identification<br>
                Number (2nd sent byte) (Hex and decimal) </td>
                <td valign="top">Description</td>
                <td align="center" valign="top">2nd Byte</td>
                <td align="center" valign="top">3rd Byte</td>
                <td align="center" valign="top">4th Byte</td>
                <td align="center" valign="top">5th Byte</td>
                <td align="center" valign="top">6th Byte</td>
                <td align="center" valign="top">7th Byte</td>
                <td align="center" valign="top">8th Byte</td>
            </tr>
            <tr>
                <td valign="top">0x00<p>0 </p>
                </td>
                <td valign="top">Wombat Application Firmware
                Version Number</td>
                <td align="center" valign="top" colspan="2">Major
                Revision Number</td>
                <td align="center" valign="top" colspan="2">Minor
                Revision Number</td>
                <td align="center" valign="top" colspan="2">Interm
                Release Number</td>
                <td align="center" valign="top">Unused</td>
            </tr>
            <tr>
                <td valign="top">0x01<p>1</p>
                </td>
                <td valign="top"><strong>18F4620 Configuration
                Bits</strong>. Values from flash addresses
                0x300001 through 0x300007. See the 18F4620 Data
                Sheet for their meanings. These are included to
                assist in debugging when a problem report is
                submitted to serialwombat.com.</td>
                <td align="center" valign="top">Contents of
                0x300001</td>
                <td align="center" valign="top">Contents of
                0x300002</td>
                <td align="center" valign="top">Contents of
                0x300003</td>
                <td align="center" valign="top">Contents of
                0x300004</td>
                <td align="center" valign="top">Contents of
                0x300005</td>
                <td align="center" valign="top">Contents of
                0x300006</td>
                <td align="center" valign="top">Contents of
                0x300007</td>
            </tr>
            <tr>
                <td valign="top">0x02<p>2</p>
                </td>
                <td valign="top"><strong>18F4620 Configuration
                Bits</strong>. Values from flash addresses
                0x300008 through 0x30000D, and 0x3FFFFE. See the
                18F4620 Data Sheet for their meanings. These are
                included to assist in debugging when a problem
                report is submitted to serialwombat.com.</td>
                <td align="center" valign="top">Contents of
                0x300008</td>
                <td align="center" valign="top">Contents of
                0x300009</td>
                <td align="center" valign="top">Contents of
                0x30000A</td>
                <td align="center" valign="top">Contents of
                0x30000B</td>
                <td align="center" valign="top">Contents of
                0x30000C</td>
                <td align="center" valign="top">Contents of
                0x30000D</td>
                <td align="center" valign="top">Contents of
                0x3FFFFE</td>
            </tr>
            <tr>
                <td valign="top">0x03<p>3</p>
                </td>
                <td valign="top"><strong>18F4620 Configuration
                Bits</strong>. Values from flash address
                0x3FFFFF. See the 18F4620 Data Sheet for their
                meanings. These are included to assist in
                debugging when a problem report is submitted to
                serialwombat.com.</td>
                <td align="center" valign="top">Contents of
                0x3FFFFF</td>
                <td align="center" valign="top">Unused</td>
                <td align="center" valign="top">Unused</td>
                <td align="center" valign="top">Unused</td>
                <td align="center" valign="top">Unused</td>
                <td align="center" valign="top">Unused</td>
                <td align="center" valign="top">Unused</td>
            </tr>
            <tr>
                <td>0x04<p>4</p>
                </td>
                <td><strong>Frame Counters</strong>. These
                numbers indicate the number of times the Frame
                Timer Interrupt has gone off, and the number of
                times that a Frame has been serviced. These are
                useful for evaluations of throughput.</td>
                <td valign="top" colspan="4">This 32-bit value
                indicates the number of times the Frame Timer
                Interrupt has fired. If this interrupt fires
                every 1ms, this value will roll-over from
                0xFFFFFFFF to 0 in approximately 50 days. This
                number is reset to 0 when the Wombat is reset.</td>
                <td valign="top" colspan="3">This 24-bit value
                indicates the number of frames that have been
                serviced. If this value differs by more than one
                from the Frame Timer Interrupt Count, the Wombat
                may be set up to do more work than the processor
                can handle.</td>
            </tr>
            <tr>
                <td valign="top">0x09<p>5</p>
                </td>
                <td valign="top"><strong>Free Running Timer</strong><p>A
                2 MHz 24 bit free running timer is used to
                timestamp the transitions detected by the
                Hardware Pulse Measurement channel mode. This 24
                bit timer can be accessed by the host through
                this interface. User should be aware that some
                time will elapse between the reading of the timer
                and the return of the data through the serial
                connection. This timer rolls over approximately
                every 8.4 seconds.</p>
                </td>
                <td valign="top">Unused. Echos 0x09</td>
                <td valign="top">Free Running Timer High Byte</td>
                <td valign="top">Free Running Timer Middle Byte</td>
                <td valign="top">Free Running Timer Low Byte</td>
                <td valign="top">Unused</td>
                <td valign="top">Unused</td>
                <td valign="top">Unused</td>
            </tr>
            <tr>
                <td valign="top">0x0D<p>13</p>
                </td>
                <td valign="top"><strong>Reset Registers</strong>
                <p>This command returns the 18F4620 RCON and
                STKPTR values captured immediately after startup.
                See the 18F4620 datasheet or the wombat.cs class
                in the WombatPanel application for more info on
                how to interpret this data.</p>
                </td>
                <td valign="top">Echos 0x0D</td>
                <td valign="top">RCON register</td>
                <td valign="top">STKPTR register</td>
                <td valign="top">Unused</td>
                <td valign="top">Unused</td>
                <td valign="top">Unused</td>
                <td valign="top">&nbsp;</td>
            </tr>
        </table>
        </td>
    </tr>
    <tr>
        <td valign="top"><h3><a name="SetSystemParameter">Set
        System Parameter</a></h3>
        <p>0x97<br>
        151</p>
        </td>
        <td valign="top" width="95%">This command is used to set
        various system wide- parameters. The 2nd byte of the
        transmitted message is the System Parameter number. The
        3rd through 8th bytes vary in meaning depending on the
        System Parameter number. Unless otherwise indicated the
        command received by the Wombat will be echoed back to the
        host upon successful completion of the setting the System
        Parameter.<p>This command exists to bridge the gap
        between two Wombat <a href="overview.htm#principles">principles</a>.
        It allows the user to modify registers which are specific
        to the 18F4620. At the same time, it contains the need to
        know about these registers to a single command.</p>
        <table border="1">
            <tr>
                <td valign="top">System Parameter Number (2nd
                sent byte)<br>
                (Hex and decimal)</td>
                <td valign="top">Description</td>
                <td align="center" valign="top">3rd Byte</td>
                <td align="center" valign="top">4th Byte</td>
                <td align="center" valign="top">5th Byte</td>
                <td align="center" valign="top">6th Byte</td>
                <td align="center" valign="top">7th Byte</td>
                <td align="center" valign="top">8th Byte</td>
            </tr>
            <tr>
                <td valign="top">0x00<p>0 </p>
                </td>
                <td valign="top"><strong>Baud Rate</strong>. This
                command allows the user to specifically configure
                the baud rate registers of the 18F4620. This
                allows the user to select non-standard baud
                rates, and may be used in the future to change
                baud rates if a clock source other than the
                internal oscillator is used. See the 18F4620 for
                defintions. This command will not issue a
                response. Caution should be used in executing
                this command, as improper settings may prevent
                the Wombat from communicating until a power cycle
                occurs. If autobaud is enabled, then the next
                character received by the Wombat should be the
                resync character.</td>
                <td align="center" valign="top">SPBRGH Register</td>
                <td align="center" valign="top">SPBRG Register</td>
                <td align="center" valign="top">BRGH bit (0 or 1)</td>
                <td align="center" valign="top">Autobaud enable
                bit (0 or 1)</td>
                <td align="center" valign="top" colspan="2">Unused</td>
            </tr>
            <tr>
                <td valign="top">0x01<p>1</p>
                </td>
                <td valign="top"><strong>Port B (pins 33 through
                40) internal pullup resistor enable</strong>.
                Pull-up resistors are used most often with
                various types of switches and other input devices
                that sometimes conduct and sometimes don't. When
                the switch is active, it connects an input pin to
                ground, yielding a 0 input. When the switch is
                inactive, the pull-up resistor pulls the pin
                high, yielding a 1 input. The internal pullup
                resistors are enabled by default. This makes pins
                33 through 40 ideal for button, switch, keypad
                and rotary encoder inputs, as the need for an
                external pull-up resistor is eliminated.</td>
                <td valign="top">0: Disable internal pull-up
                resistors<p>1: Enable internal pullup resistors</p>
                </td>
                <td valign="top" colspan="5">Unused</td>
            </tr>
            <tr>
                <td valign="top">0x02<br>
                2</td>
                <td valign="top"><strong>Pin Service Start and
                End</strong>. This parameter allows the user to
                specify a range of pins to be serviced in each
                frame. By default, all pins (1 through 40) are
                serviced. However, servicing every pin can
                consume substantial system throughput even if the
                pins are not doing anything. By reducing the
                number of pins which are serviced by each frame
                the time between pin servicings can be as short
                as 100us.</td>
                <td valign="top">Start Pin. This must be between
                1 and the number of physical pins (40 on the
                18F4620 based Serial Wombat)</td>
                <td valign="top">End Pin. This must be between
                the Start Pin value and the number of physical
                pins.</td>
                <td valign="top" colspan="4">Unused</td>
            </tr>
            <tr>
                <td>0x03<br>
                3</td>
                <td><strong>Reset Systime</strong>. Calling this
                parameter resets the Frame Counters from the 0x04
                Get System Info command to zero. It has no
                parameters.</td>
                <td colspan="6">Unused.</td>
            </tr>
            <tr>
                <td valign="top">0x04<br>
                4</td>
                <td valign="top"><strong>Frame Counter Reset
                Value</strong>. This value is used to determine
                the the amount of time between the start of one
                frame and the start of the next frame. It is used
                to set Timer 0 of the 18F4620. The 16 bit value
                of this timer can be determined by the following
                equation:<p>Reset_value = 65532 - (Timer Clock
                Frequency/ Frames_Per_Second)</p>
                <p>If the result is negative, use a slower timer
                clock frequency.</p>
                <p>For example, the value for 500 frames per
                second with an 8000000 clock is 49532, or 0xC17C.</p>
                <p>The value for 50 frames per second (20ms
                frames) with a 1,000,000 clock is 45536, or
                0xB1E0.</p>
                <p>Note that this command did not work properly
                before firmware Revision 1.2.0</p>
                </td>
                <td valign="top" colspan="2">Reset Value (16
                bits)</td>
                <td valign="top">Clock Frequency:<p>0: 8MHz<br>
                1: 4MHz<br>
                2: 2MHz<br>
                3: 1MHz<br>
                4: 500 kHz<br>
                5: 250 kHz<br>
                6: 125 kHz<br>
                7: 62.5kHz</p>
                </td>
                <td valign="top" colspan="3">&nbsp;</td>
            </tr>
            <tr>
                <td valign="top">0x05<br>
                5</td>
                <td valign="top"><strong>Enable Throughput Pin
                Output</strong>. Sets pin 6 to display when the
                processor is busy servicing an interrupt or the
                periodic frame. See the Throughput section of the
                documentation for more information. (Coming soon)</td>
                <td valign="top">0: Pin 4 is a standard pin<p>1:
                Pin 4 shows processor utilization</p>
                </td>
                <td valign="top" colspan="5">Unused</td>
            </tr>
            <tr>
                <td valign="top">0x06<br>
                6</td>
                <td><a name="ConfigureAnalogChannels"><strong>Number
                of Analog Channels</strong></a><strong>. </strong>The
                Wombat may have 0 to 13 pins configured as analog
                input channels. Each channel configured as an
                analog input uses some time out of the periodic
                frame to do its conversion. By default, 4 pins
                are set to analog inputs. For each number of
                analog inputs, specific pins become analog
                inputs. This is a property of the 18F4620 chip,
                and cannot be altered:<table border="0">
                    <tr>
                        <td># of analog pins:</td>
                        <td>&nbsp;</td>
                        <td>Analog pin numbers:</td>
                    </tr>
                    <tr>
                        <td>0</td>
                        <td>&nbsp;</td>
                        <td>-</td>
                    </tr>
                    <tr>
                        <td>1</td>
                        <td>&nbsp;</td>
                        <td><strong>2</strong></td>
                    </tr>
                    <tr>
                        <td>2</td>
                        <td>&nbsp;</td>
                        <td>2,<strong>3</strong></td>
                    </tr>
                    <tr>
                        <td>3</td>
                        <td>&nbsp;</td>
                        <td>2,3,<strong>4</strong></td>
                    </tr>
                    <tr>
                        <td>4</td>
                        <td>&nbsp;</td>
                        <td>2,3,4,<strong>5</strong></td>
                    </tr>
                    <tr>
                        <td>5</td>
                        <td>&nbsp;</td>
                        <td>2,3,4,5,<strong>7</strong></td>
                    </tr>
                    <tr>
                        <td>6</td>
                        <td>&nbsp;</td>
                        <td>2,3,4,5,7,<strong>8</strong></td>
                    </tr>
                    <tr>
                        <td>7</td>
                        <td>&nbsp;</td>
                        <td>2,3,4,5,7,8,<strong>9</strong></td>
                    </tr>
                    <tr>
                        <td>8</td>
                        <td>&nbsp;</td>
                        <td>2,3,4,5,7,8,9,<strong>10</strong></td>
                    </tr>
                    <tr>
                        <td>9</td>
                        <td>&nbsp;</td>
                        <td>2,3,4,5,7,8,9,10,<strong>35</strong></td>
                    </tr>
                    <tr>
                        <td>10</td>
                        <td>&nbsp;</td>
                        <td>2,3,4,5,7,8,9,10,35,<strong>36</strong></td>
                    </tr>
                    <tr>
                        <td>11</td>
                        <td>&nbsp;</td>
                        <td>2,3,4,5,7,8,9,10,<strong>34</strong>,35,36</td>
                    </tr>
                    <tr>
                        <td>12</td>
                        <td>&nbsp;</td>
                        <td>2,3,4,5,7,8,9,10,34,35,36,<strong>37</strong></td>
                    </tr>
                    <tr>
                        <td>13</td>
                        <td>&nbsp;</td>
                        <td>2,3,4,5,7,8,9,10,<strong>33</strong>,34,
                        35,36,37</td>
                    </tr>
                </table>
                <p>After issuing this command it is left to the
                user to properly update all of the pins which
                have changed function to a mode which is
                compatible with that function.</p>
                </td>
                <td valign="top">Number of Analog Channels</td>
                <td colspan="5">&nbsp;</td>
            </tr>
            <tr>
                <td>0x19<br>
                25</td>
                <td>Configure Timer Base I/O</td>
                <td colspan="6"><a href="timerinterrupt.htm">See
                the page on this feature.</a></td>
            </tr>
            <tr>
                <td>0x1C<br>
                28</td>
                <td>Enable / disable and Set Pin to be used as
                CTS pin (0 disables this feature, which is the
                default setting). The Wombat will delay sending
                response packets if the CTS pin is high. When
                this setting is configured it is also stored in
                EEPROM for use at subsequent power-ups.</td>
                <td>0: Disable CTS functionality<br>
                1: Enable</td>
                <td>Pin to configure to CTS</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td>0x1E<br>
                30</td>
                <td valign="top"><a name="ConfigureSPI"><strong>Configure
                Wombat SPI Slave Settings</strong></a><br>
                Allows your Wombat to be controlled via SPI in
                addition to UART. Values will be written to
                EEPROM.</td>
                <td valign="top">0: Disable SPI Slave
                Functionality<br>
                1: Enable SPI Slave Functionality</td>
                <td valign="top">SSPSTAT:<br>
                the value to be written to the SSPSTAT register
                at Powerup. See 18F4620 datasheet for details.</td>
                <td valign="top">SSPCON1:<br>
                the value to be written to the SSPSTAT register
                at Powerup. See 18F4620 datasheet for details.</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td>0x1F<br>
                31</td>
                <td valign="top"><a
                name="ConfigureAddressByCommand"><strong>Configure
                Wombat Address By Command.</strong></a> Sets the
                Wombat's communication address to a value
                specified by the host. See <a href="#multiple">Addressing
                and Multiple Wombats</a>, above. This command
                does not echo a response.</td>
                <td>Number between 0 and 254 (excluding 0x55)
                representing the commanding Address</td>
                <td>If 'E' then the address will be written to
                EEPROM, and that address used on subsequent
                power-ups. Set to 0x55 otherwise.</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td>0x20<br>
                32</td>
                <td valign="top"><a name="ConfigureAddressByPins"><strong>Configure
                Wombat Address By Pins.</strong></a> Sets the
                Wombat's communication address to a value
                specified by the host. See <a href="#multiple">Addressing
                and Multiple Wombats</a>, above. This command
                does not echo a response.</td>
                <td>Pin number of 0x10 bit of Address ( use pin 0
                for 0).</td>
                <td>Pin number of 0x08 bit of Address ( use pin 0
                for 0).</td>
                <td>Pin number of 0x04 bit of Address ( use pin 0
                for 0).</td>
                <td>Pin number of 0x02bit of Address ( use pin 0
                for 0).</td>
                <td>Pin number of 0x01 bit of Address ( use pin 0
                for 0).</td>
                <td>If 'E' then the address will be written to
                EEPROM, and that address used on subsequent
                power-ups. Set to 0x55 otherwise.</td>
            </tr>
            <tr>
                <td>0x21<br>
                33</td>
                <td valign="top"><a name="ConfigureAddressByA2D2"><strong>Configure
                Wombat Address By A/D (2 bit).</strong></a> Sets
                the Wombat's communication address to a value
                specified the A/D conversion of a given pin. See <a
                href="#multiple">Addressing and Multiple Wombats</a>,
                above. This command does not echo a response.</td>
                <td>Pin number of analog capable pin to determine
                address.</td>
                <td>If 'E' then the address will be written to
                EEPROM, and that address used on subsequent
                power-ups. Set to 0x55 otherwise.</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td>0x22<br>
                34</td>
                <td valign="top"><a name="ConfigureAddressByA2D2"><strong>Configure
                Wombat Address By A/D (4 bit).</strong></a> Sets
                the Wombat's communication address to a value
                specified the A/D conversion of a given pin. See <a
                href="#multiple">Addressing and Multiple Wombats</a>,
                above. This command does not echo a response.</td>
                <td>Pin number of analog capable pin to determine
                address.</td>
                <td>If 'E' then the address will be written to
                EEPROM, and that address used on subsequent
                power-ups. Set to 0x55 otherwise.</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
        </table>
        </td>
    </tr>
    <tr>
        <td valign="top"><h3><a name="ConfigurePin1to28">Configure
        Pins 1 to 28</a></h3>
        <p>0xA0<br>
        160</p>
        </td>
        <td valign="top">This command is used to modify numerous
        pins with one command. The command uses 28 two-bit
        entries to represent the action for each pin:<table
        border="0">
            <tr>
                <td>Value</td>
                <td>Pin State</td>
            </tr>
            <tr>
                <td>00</td>
                <td>Low</td>
            </tr>
            <tr>
                <td>01</td>
                <td>High</td>
            </tr>
            <tr>
                <td>10 </td>
                <td>Input</td>
            </tr>
            <tr>
                <td>11</td>
                <td>Unchanged</td>
            </tr>
        </table>
        <p>Pin 1 is represented by the two least-significant bits
        in the 2nd byte. Pin 4 is represented by the two
        most-significant bits in the 2nd byte. Pin 5 is
        represented by the two least-significant bits in the 3rd
        byte. Pin 28 is represented by the two most significant
        bits in the 7th byte.</p>
        <p>The pins do not simultaneously change state. If
        requested, Pin 1 will change state first, followed by Pin
        2, followed by Pin 3, and so on through pin 28. Pins
        which are acted on by this command change mode to
        CHANNEL_MODE_DIRECT.</p>
        <p>This command is echoed back to the host upon
        completion.</p>
        <p>Example: <font color="#008000">Set pin 1 to Low</font>,
        <font color="#FF0000">pin 6 to High</font>, <font
        color="#800080">pin 19 to Input</font>, and <font
        color="#808000">pin 25 to Low</font>. Leave all other
        pins unchanged.</p>
        <table border="1" width="100%">
            <tr>
                <td valign="top">Data Sent to the Wombat:</td>
                <td valign="top" width="10%">0xA0</td>
                <td valign="top" width="10%">0xFC</td>
                <td valign="top" width="10%">0xF7</td>
                <td valign="top" width="10%">0xFF</td>
                <td valign="top" width="10%">0xFF</td>
                <td valign="top" width="10%">0xEF</td>
                <td valign="top" width="10%">0xFF</td>
                <td valign="top" width="10%">0xFC</td>
            </tr>
            <tr>
                <td>Binary:</td>
                <td>&nbsp;</td>
                <td>111111<font color="#008000">00</font></td>
                <td>1111<font color="#FF0000">01</font>11</td>
                <td>11111111</td>
                <td>11111111</td>
                <td>11<font color="#800080">10</font>1111</td>
                <td>11111111</td>
                <td>111111<font color="#808000">00</font></td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="10%">Configure Pins 1 to
                28</td>
                <td valign="top" width="6%">Pins 1 to 4</td>
                <td valign="top" width="6%">Pins 5 to 8</td>
                <td valign="top" width="6%">Pins 9 to 12</td>
                <td valign="top" width="6%">Pins 13 to 16</td>
                <td valign="top" width="2%">Pins 17 to 20</td>
                <td valign="top" width="2%">Pins 21 to 24</td>
                <td valign="top" width="2%">Pins 25 to 28</td>
            </tr>
        </table>
        </td>
    </tr>
    <tr>
        <td valign="top"><h3><a name="ConfigurePin1to28">Configure
        Pins 13 to </a>40</h3>
        <p>0xA1<br>
        161</p>
        </td>
        <td valign="top">This command is used to modify numerous
        pins with one command and works in the same manner as
        Configure Pins 1 to 28, but operates on a different range
        of pins.<p>Pin 13 is represented by the two
        least-significant bits in the 2nd byte. Pin 14 is
        represented by the two most-significant bits in the 2nd
        byte. Pin 17 is represented by the two least-significant
        bits in the 3rd byte. Pin 40 is represented by the two
        most significant bits in the 7th byte.</p>
        <p>The pins do not simultaneously change state. If
        requested, Pin 13 will change state first, followed by
        Pin 14, followed by Pin 15, and so on through pin 40.
        Pins which are acted on by this command change mode to
        CHANNEL_MODE_DIRECT.</p>
        <p>This command is echoed back to the host upon
        completion.</p>
        <p>Example: <font color="#008000">Set pin 17 to Low</font>,
        <font color="#FF0000">pin 18 to High</font>, <font
        color="#800080">pin 19 to Input</font>, and <font
        color="#808000">pin 39 to Low</font>. Leave all other
        pins unchanged.</p>
        <table border="1" width="100%">
            <tr>
                <td valign="top">Data Sent to the Wombat:</td>
                <td valign="top" width="10%">0xA1</td>
                <td valign="top" width="10%">0xFF</td>
                <td valign="top" width="10%">0xE4</td>
                <td valign="top" width="10%">0xFF</td>
                <td valign="top" width="10%">0xFF</td>
                <td valign="top" width="10%">0xFF</td>
                <td valign="top" width="10%">0xFF</td>
                <td valign="top" width="10%">0xCF</td>
            </tr>
            <tr>
                <td>Binary:</td>
                <td>&nbsp;</td>
                <td>11111111</td>
                <td>11<font color="#800080">10</font><font
                color="#FF0000">01</font><font color="#008000">00</font></td>
                <td>11111111</td>
                <td>11111111</td>
                <td>11111111</td>
                <td>11111111</td>
                <td>11<font color="#808000">00</font>1111</td>
            </tr>
            <tr>
                <td valign="top">Meaning:</td>
                <td valign="top" width="10%">Configure Pins 13 to
                40</td>
                <td valign="top" width="6%">Pins 13 to 16</td>
                <td valign="top" width="6%">Pins 17 to 20</td>
                <td valign="top" width="6%">Pins 21 to 24</td>
                <td valign="top" width="6%">Pins 25 to 28</td>
                <td valign="top" width="2%">Pins 29 to 32</td>
                <td valign="top" width="2%">Pins 33 to 36</td>
                <td valign="top" width="2%">Pins 37 to 40</td>
            </tr>
        </table>
        </td>
    </tr>
    <tr>
        <td valign="top"><h3><a name="ConfigureChannelMode">Configure
        Channel Mode</a></h3>
        <p>0xC8 through 0xD1</p>
        <p>200 thorugh 209</p>
        </td>
        <td valign="top">The Configure Channel Mode command
        allows the host to configure a Wombat Pin or Channel to a
        specific function. For each Channel Mode one or more
        configuration commands will be defined. Some channel
        modes such as CHANNEL_MODE_ROTARY_ENCODER require more
        than one command to complete initialization. Other
        commands, such as CHANNEL_MODE_PWM_FOLLOW_DIRECT have
        multiple interfaces, one simple, and one which is more
        powerful but longer and more complicated. When a channel
        has multiple initialization commands they are
        differentiated by which command byte (200 through 209) is
        used to send the message.<p>See the section on <a
        href="doc.htm#Channel_Modes">channel modes</a> for
        specific configuration commands for each channel mode.</p>
        </td>
    </tr>

