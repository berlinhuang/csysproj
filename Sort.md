

<table>
    <tr><td rowspan = "2">type</td><td  rowspan = "2">sort</td><td colspan="3" align="center">time</td><td>space</td><td rowspan = "2">stable</td></tr>
    <tr><td>average</td><td>best</td><td>worst</td><td>space</td></tr>
    <tr><td rowspan = "3">insert</td><td>insert</td><td>o(n2)</td><td>o(n)</td><td>o(n2)</td><td>o(1)</td><td>Y</td></tr>
    <tr><td>bininsert</td><td></td><td></td><td></td><td></td><td></td></tr>
    <tr><td>shell</td><td>o(n1.3)</td><td>o(n)</td><td>o(n2)</td><td>o(1)</td><td>N</td></tr>
    <tr><td rowspan = "2">swap</td><td>bubble</td><td>o(n2)</td><td>o(n)</td><td>o(n2)</td><td>o(1)</td><td>Y</td></tr>
    <tr><td>quick</td><td>O(N*log2N)</td><td>O(N*log2N)</td><td>o(n2)</td><td>O(log2n)~O(n)</td><td>N</td></tr>
    <tr><td rowspan = "2">select</td><td>insert</td><td>o(n2)</td><td>o(n)</td><td>o(n2)</td><td>o(1)</td><td>N</td></tr>
    <tr><td>heapsort</td><td>O(N*log2N)</td><td>O(N*log2N)</td><td>O(N*log2N)</td><td>o(1)</td><td>N</td></tr>
</table>