# Two Pointers 

## Manacher's Algorithm Implementation (palindrome subpattern)

### When to use

* Palindrome-centric tasks (especially **longest palindromic substring** / “expand from a center”).
* You can define a **center** and grow **left/right** symmetrically to test/extend a palindrome.
* Note: **Manacher’s** is specific to palindromic-substring style problems; it’s not a general replacement for other two-pointer families.

### Core definition (theory/trick behind the pattern)

* **Expand-around-center:** treat each index (and each gap) as a potential center and expand `l--/r++` while `s[l]==s[r]`.
* **Manacher’s:** preprocess with sentinels + separators so odd/even unify (e.g. `@#a#b#a#$`). Track the **current rightmost palindrome bounds** via `left_bound/right_bound` (inclusive, in the transformed string) and keep `radii[i]`.

  * Mirror index: `mirror = left_bound + right_bound - i`.
  * Symmetry reuse: if `i < right_bound`, set `radii[i] = min(right_bound - i, radii[mirror])`, else `0`.
  * Expand: while `s[i + 1 + radii[i]] == s[i - 1 - radii[i]]`, increment `radii[i]`.
  * If `i + radii[i] > right_bound`, update bounds: `left_bound = i - radii[i]`, `right_bound = i + radii[i]`.

### Simplified Example

* Transform e.g. `babad` → `@#b#a#b#a#d#$` (sentinels @, $).
* Each transformed index `i` has radius `radii[i]`; the answer comes from `max(radii[i])` mapped back to original indices.
* The `[Center,Radius]` bookkeeping lets you reuse symmetry so most positions avoid full re-expansion.
* This gives the radius for all palindromes found in the radii array, output all the strings with largest radius and scrub expansion characters out of them ('@#$').

### Common pitfalls

* Bounds/edge handling during expansion; sentinels help, but off-by-one around `i ± (1 + radii[i])` still bites.
* Edge cases: empty / length-1 strings; sentinels/separators; mapping transformed indices back to the original string.
* Off-by-one when resetting `l/r` for a new center (especially in Manacher-style symmetry bookkeeping).

### Complexity

* Time: typically **O(n^2)** for expand-around-center; **O(n)** for Manacher’s.
* Space: typically **O(1)** for expand-around-center; **O(n)** for Manacher’s.

## Variant Complexities and tradeoffs

| Variant                |   Time |    Space | Tradeoff / Notes                                                                                                 |
| ---------------------- | -----: | -------: | ---------------------------------------------------------------------------------------------------------------- |
| Baseline (brute force) | O(n^3) | O(1) | Proof-of-concept only; quickly becomes too slow.                                                                 |
| Expand-around-center   | O(n^2) |     O(1) | Much simpler than Manacher; often acceptable; still worst-case quadratic.                                        |
| Manacher’s             |   O(n) |     O(n) | Best asymptotics for longest palindromic substring; more bookkeeping (bounds + mirror + radii) and mapping back. |

