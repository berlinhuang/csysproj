

<table>
    <tr><td rowspan = "2">type</td><td  rowspan = "2">sort</td><td colspan="3" align="center">time</td><td>space</td><td rowspan = "2">stable</td></tr>
    <tr><td>average</td><td>best</td><td>worst</td><td>space</td></tr>
    <tr><td rowspan = "3">insert</td><td>insert</td><td>O(n2)</td><td>O(n)</td><td>O(n2)</td><td>O(1)</td><td>Y</td></tr>
    <tr><td>bininsert</td><td></td><td></td><td></td><td></td><td></td></tr>
    <tr><td>shell</td><td>O(n1.3)</td><td>O(n)</td><td>O(n2)</td><td>O(1)</td><td>N</td></tr>
    <tr><td rowspan = "2">swap</td><td>bubble</td><td>O(n2)</td><td>O(n)</td><td>O(n2)</td><td>O(1)</td><td>Y</td></tr>
    <tr><td>quick</td><td>O(N*log2N)</td><td>O(N*log2N)</td><td>O(n2)</td><td>O(nlog2n)</td><td>N</td></tr>
    <tr><td rowspan = "2">select</td><td>select</td><td>O(n2)</td><td>O(n2)</td><td>O(n2)</td><td>O(1)</td><td>N</td></tr>
    <tr><td>heapsort</td><td>O(N*log2N)</td><td>O(N*log2N)</td><td>O(N*log2N)</td><td>O(1)</td><td>N</td></tr>
    <tr><td colspan = "2" align = "center">merge</td><td>O(N*log2N)</td><td>O(N*log2N)</td><td>O(N*log2N)</td><td>O(n)</td><td>Y</td></tr>
</table>



> QuickSort
- 就空间复杂度来说，主要是递归造成的栈空间的使用，由数学归纳法可证明，其数量级为O(nlogn)，
- 最好情况，递归树的深度为log2n，其空间复杂度也就为O(logn)，
- 最坏情况，需要进行n‐1递归调用，其空间复杂度为O(n)，
- 平均情况，空间复杂度也为O(logn)