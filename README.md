# Data Format of Files Produced by MAKA

## MAKA File Header

<style type="text/css">
.tg  {border-collapse:collapse;border-spacing:0;}
.tg td{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  overflow:hidden;padding:10px 5px;word-break:normal;}
.tg th{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  font-weight:normal;overflow:hidden;padding:10px 5px;word-break:normal;}
.tg .tg-vxga{background-color:#ffffff;text-align:center;vertical-align:middle}
.tg .tg-h47o{background-color:#8abb8a;text-align:center;vertical-align:middle}
</style>
<table class="tg">
<thead>
  <tr>
    <th class="tg-vxga">31</th>
    <th class="tg-vxga">30</th>
    <th class="tg-vxga">29</th>
    <th class="tg-vxga">28</th>
    <th class="tg-vxga">27</th>
    <th class="tg-vxga">26</th>
    <th class="tg-vxga">25</th>
    <th class="tg-vxga">24</th>
    <th class="tg-vxga">23</th>
    <th class="tg-vxga">22</th>
    <th class="tg-vxga">21</th>
    <th class="tg-vxga">20</th>
    <th class="tg-vxga">19</th>
    <th class="tg-vxga">18</th>
    <th class="tg-vxga">17</th>
    <th class="tg-vxga">16</th>
    <th class="tg-vxga">15</th>
    <th class="tg-vxga">14</th>
    <th class="tg-vxga">13</th>
    <th class="tg-vxga">12</th>
    <th class="tg-vxga">11</th>
    <th class="tg-vxga">10</th>
    <th class="tg-vxga">9</th>
    <th class="tg-vxga">8</th>
    <th class="tg-vxga">7</th>
    <th class="tg-vxga">6</th>
    <th class="tg-vxga">5</th>
    <th class="tg-vxga">4</th>
    <th class="tg-vxga">3</th>
    <th class="tg-vxga">2</th>
    <th class="tg-vxga">1</th>
    <th class="tg-vxga">0</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td class="tg-h47o" colspan="32">Known word:   0xB01ADEEE</td>
  </tr>
  <tr>
    <td class="tg-h47o" colspan="32">UNIX time of the   run</td>
  </tr>
  <tr>
    <td class="tg-h47o" colspan="32">MAKA git hash</td>
  </tr>
  <tr>
    <td class="tg-h47o" colspan="4">Type</td>
    <td class="tg-h47o" colspan="12">Data Version</td>
    <td class="tg-h47o" colspan="16" rowspan="2">Detectors connected</td>
  </tr>
  <tr>
    <td class="tg-h47o">tc</td>
    <td class="tg-h47o">cal</td>
    <td class="tg-h47o">hk</td>
    <td class="tg-h47o">sc</td>
    <td class="tg-h47o" colspan="4">Major</td>
    <td class="tg-h47o" colspan="4">Minor</td>
    <td class="tg-h47o" colspan="4">Patch</td>
  </tr>
  <tr>
    <td class="tg-h47o" colspan="16">Detector ID 1</td>
    <td class="tg-h47o" colspan="16">Detector ID 0</td>
  </tr>
  <tr>
    <td class="tg-h47o" colspan="16">Detector ID N-1</td>
    <td class="tg-h47o" colspan="16">…</td>
  </tr>
</tbody>
</table>

## MAKA Event Header + Payload

<style type="text/css">
.tg  {border-collapse:collapse;border-spacing:0;}
.tg td{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  overflow:hidden;padding:10px 5px;word-break:normal;}
.tg th{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  font-weight:normal;overflow:hidden;padding:10px 5px;word-break:normal;}
.tg .tg-vxga{background-color:#ffffff;text-align:center;vertical-align:middle}
.tg .tg-h47o{background-color:#8abb8a;text-align:center;vertical-align:middle}
.tg .tg-vhtn{background-color:#ffffff;border-color:#000000;text-align:center;vertical-align:middle}
</style>
<table class="tg">
<thead>
  <tr>
    <th class="tg-vxga">31</th>
    <th class="tg-vxga">30</th>
    <th class="tg-vxga">29</th>
    <th class="tg-vxga">28</th>
    <th class="tg-vxga">27</th>
    <th class="tg-vxga">26</th>
    <th class="tg-vxga">25</th>
    <th class="tg-vxga">24</th>
    <th class="tg-vxga">23</th>
    <th class="tg-vxga">22</th>
    <th class="tg-vxga">21</th>
    <th class="tg-vxga">20</th>
    <th class="tg-vxga">19</th>
    <th class="tg-vxga">18</th>
    <th class="tg-vxga">17</th>
    <th class="tg-vxga">16</th>
    <th class="tg-vxga">15</th>
    <th class="tg-vxga">14</th>
    <th class="tg-vxga">13</th>
    <th class="tg-vxga">12</th>
    <th class="tg-vxga">11</th>
    <th class="tg-vxga">10</th>
    <th class="tg-vxga">9</th>
    <th class="tg-vxga">8</th>
    <th class="tg-vxga">7</th>
    <th class="tg-vxga">6</th>
    <th class="tg-vxga">5</th>
    <th class="tg-vxga">4</th>
    <th class="tg-vxga">3</th>
    <th class="tg-vxga">2</th>
    <th class="tg-vxga">1</th>
    <th class="tg-vxga">0</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td class="tg-h47o" colspan="32">Known word:   0xFA4AF1CA</td>
  </tr>
  <tr>
    <td class="tg-h47o" colspan="32">Length in bytes</td>
  </tr>
  <tr>
    <td class="tg-h47o" colspan="32">Event Number</td>
  </tr>
  <tr>
    <td class="tg-h47o" colspan="4">Type</td>
    <td class="tg-h47o" colspan="12">Status</td>
    <td class="tg-h47o" colspan="16">Detectors in the event</td>
  </tr>
  <tr>
    <td class="tg-vhtn" colspan="32">Payload 0</td>
  </tr>
  <tr>
    <td class="tg-vhtn" colspan="32">…</td>
  </tr>
  <tr>
    <td class="tg-vhtn" colspan="32">Payload N-1</td>
  </tr>
</tbody>
</table>

## PAPERO Event

<style type="text/css">
.tg  {border-collapse:collapse;border-spacing:0;}
.tg td{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  overflow:hidden;padding:10px 5px;word-break:normal;}
.tg th{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  font-weight:normal;overflow:hidden;padding:10px 5px;word-break:normal;}
.tg .tg-vxga{background-color:#ffffff;text-align:center;vertical-align:middle}
.tg .tg-3ygc{background-color:#8ABB8A;text-align:center;vertical-align:middle}
.tg .tg-nrix{text-align:center;vertical-align:middle}
.tg .tg-i93t{background-color:#83A3FF;text-align:center;vertical-align:middle}
</style>
<table class="tg">
<thead>
  <tr>
    <th class="tg-nrix">31</th>
    <th class="tg-vxga">30</th>
    <th class="tg-vxga">29</th>
    <th class="tg-vxga">28</th>
    <th class="tg-vxga">27</th>
    <th class="tg-vxga">26</th>
    <th class="tg-vxga">25</th>
    <th class="tg-vxga">24</th>
    <th class="tg-vxga">23</th>
    <th class="tg-vxga">22</th>
    <th class="tg-vxga">21</th>
    <th class="tg-vxga">20</th>
    <th class="tg-vxga">19</th>
    <th class="tg-vxga">18</th>
    <th class="tg-vxga">17</th>
    <th class="tg-vxga">16</th>
    <th class="tg-vxga">15</th>
    <th class="tg-vxga">14</th>
    <th class="tg-vxga">13</th>
    <th class="tg-vxga">12</th>
    <th class="tg-vxga">11</th>
    <th class="tg-vxga">10</th>
    <th class="tg-vxga">9</th>
    <th class="tg-vxga">8</th>
    <th class="tg-vxga">7</th>
    <th class="tg-vxga">6</th>
    <th class="tg-vxga">5</th>
    <th class="tg-vxga">4</th>
    <th class="tg-vxga">3</th>
    <th class="tg-vxga">2</th>
    <th class="tg-vxga">1</th>
    <th class="tg-vxga">0</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td class="tg-3ygc" colspan="32">Known word:&nbsp;&nbsp;&nbsp;0xBABA1A9A</td>
  </tr>
  <tr>
    <td class="tg-3ygc" colspan="32">Length</td>
  </tr>
  <tr>
    <td class="tg-3ygc" colspan="32">Detector git hash</td>
  </tr>
  <tr>
    <td class="tg-3ygc" colspan="32">Trigger number</td>
  </tr>
  <tr>
    <td class="tg-3ygc" colspan="16">Detector ID</td>
    <td class="tg-3ygc" colspan="16" rowspan="2">Trigger ID</td>
  </tr>
  <tr>
    <td class="tg-3ygc" colspan="8">Type</td>
    <td class="tg-3ygc" colspan="8">Progressive&nbsp;&nbsp;&nbsp;number</td>
  </tr>
  <tr>
    <td class="tg-3ygc" colspan="32">Internal Timestamp&nbsp;&nbsp;&nbsp;[63:32]</td>
  </tr>
  <tr>
    <td class="tg-3ygc" colspan="32">Internal Timestamp&nbsp;&nbsp;&nbsp;[31:0]</td>
  </tr>
  <tr>
    <td class="tg-3ygc" colspan="32">External Timestamp&nbsp;&nbsp;&nbsp;[63:32]</td>
  </tr>
  <tr>
    <td class="tg-3ygc" colspan="32">External Timestamp&nbsp;&nbsp;&nbsp;[31:0]</td>
  </tr>
  <tr>
    <td class="tg-vxga" colspan="32">Payload 0</td>
  </tr>
  <tr>
    <td class="tg-vxga" colspan="32">...</td>
  </tr>
  <tr>
    <td class="tg-vxga" colspan="32">Payload Length-11</td>
  </tr>
  <tr>
    <td class="tg-i93t" colspan="32">Known word: 0x0BEDFACE</td>
  </tr>
  <tr>
    <td class="tg-i93t" colspan="32">CRC-32 / MPEG-2, init: 0xFFFFFFFF</td>
  </tr>
</tbody>
</table>