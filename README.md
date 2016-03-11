# libco

Mirror of http://byuu.org/library/libco/

Try pandoc!

pandoc --from html --to markdown_github
Convert   from    


<b>Supported targets:</b><br/><br/>

Note that supported targets are only those that have been tested and confirmed
working. It is quite possible that libco will work on more processors, compilers
and operating systems than those listed below.
<hr/>

<b>libco.x86</b><br/>
Overhead: ~5x<br/>
Supported processor(s): 32-bit x86<br/>
Supported compiler(s): any<br/>
Supported operating system(s):<ul>
<li>Windows</li>
<li>Mac OS X</li>
<li>Linux</li>
<li>BSD</li>
</ul>
<hr/>

<b>libco.amd64</b><br/>
Overhead: ~10x (Windows), ~6x (all other platforms)<br/>
Supported processor(s): 64-bit amd64<br/>
Supported compiler(s): any<br/>
Supported operating system(s):<ul>
<li>Windows</li>
<li>Mac OS X</li>
<li>Linux</li>
<li>BSD</li>
</ul>
<hr/>

<b>libco.ppc</b><br/>
Overhead: ~20x<br/>
Supported processor(s): 32-bit PowerPC, 64-bit PowerPC<br/>
Supported compiler(s): GNU GCC<br/>
Supported operating system(s):<ul>
</ul>
<li>Mac OS X</li>
<li>Linux</li>
<li>BSD</li>
<li>Playstation 3</li>
</ul>
<br/>

Note: this module contains compiler flags to enable/disable FPU and Altivec
support.

<hr/>

<b>libco.fiber</b><br/>
Overhead: ~15x<br/>
Supported processor(s): Processor independent<br/>
Supported compiler(s): any<br/>
Supported operating system(s):<ul>
<li>Windows</li>
</ul>
<hr/>

<b>libco.sjlj</b><br/>
Overhead: ~30x<br/>
Supported processor(s): Processor independent<br/>
Supported compiler(s): any<br/>
Supported operating system(s):<ul>
<li>Mac OS X</li>
<li>Linux</li>
<li>BSD</li>
<li>Solaris</li>
</ul>
<hr/>

<b>libco.ucontext</b><br/>
Overhead: <b><font color="#ff0000">~300x</font></b><br/>
Supported processor(s): Processor independent<br/>
Supported compiler(s): any<br/>
Supported operating system(s):<ul>
<li>Linux</li>
<li>BSD</li>
</ul>
<hr/>

to    
**Supported targets:**
Note that supported targets are only those that have been tested and confirmed working. It is quite possible that libco will work on more processors, compilers and operating systems than those listed below.

------------------------------------------------------------------------

**libco.x86**
Overhead: ~5x
Supported processor(s): 32-bit x86
Supported compiler(s): any
Supported operating system(s):

-   Windows
-   Mac OS X
-   Linux
-   BSD

------------------------------------------------------------------------

**libco.amd64**
Overhead: ~10x (Windows), ~6x (all other platforms)
Supported processor(s): 64-bit amd64
Supported compiler(s): any
Supported operating system(s):

-   Windows
-   Mac OS X
-   Linux
-   BSD

------------------------------------------------------------------------

**libco.ppc**
Overhead: ~20x
Supported processor(s): 32-bit PowerPC, 64-bit PowerPC
Supported compiler(s): GNU GCC
Supported operating system(s):

<li>
Mac OS X

</li>
<li>
Linux

</li>
<li>
BSD

</li>
<li>
Playstation 3

</li>
</ul>
Note: this module contains compiler flags to enable/disable FPU and Altivec support.

------------------------------------------------------------------------

**libco.fiber**
Overhead: ~15x
Supported processor(s): Processor independent
Supported compiler(s): any
Supported operating system(s):

-   Windows

------------------------------------------------------------------------

**libco.sjlj**
Overhead: ~30x
Supported processor(s): Processor independent
Supported compiler(s): any
Supported operating system(s):

-   Mac OS X
-   Linux
-   BSD
-   Solaris

------------------------------------------------------------------------

**libco.ucontext**
Overhead: **<font color="#ff0000">~300x</font>**
Supported processor(s): Processor independent
Supported compiler(s): any
Supported operating system(s):

-   Linux
-   BSD

------------------------------------------------------------------------
pandoc 1.16.0.2

© 2013–2015 John MacFarlane

**License:**
libco is released to the public domain.

------------------------------------------------------------------------

**Contact:**
At present, you may contact me at setsunakun0 at hotmail dot com.
I am interested in knowing of any projects that make use of this library, though this is only a courtesy.

------------------------------------------------------------------------

**Foreword:**
libco is a cross-platform, public domain implementation of cooperative-multithreading; a feature that is sorely lacking from the ISO C/C++ standard.
The library is designed for maximum speed and portability, and not for safety or features. If safety or extra functionality is desired, a wrapper API can easily be written to encapsulate all library functions.
Behavior of executing operations that are listed as not permitted below result in undefined behavior. They may work anyway, they may cause undesired / unknown behavior, or they may crash the program entirely.
The goal of this library was to simplify the base API as much as possible, implementing only that which cannot be implemented using pure C. Additional functionality after this would only complicate ports of this library to new platforms.

------------------------------------------------------------------------

**Porting:**
This document is included as a reference for porting libco. Please submit any ports you create to me, so that libco can become more useful. Please note that since libco is public domain, you must submit your code as a work of the public domain in order for it to be included in the official distribution. Full credit will be given in the source code of the official release. Please do not bother submitting code to me under any other license – including GPL, LGPL, BSD or CC – I am not interested in creating a library with multiple different licenses depending on which targets are used.

------------------------------------------------------------------------

**Synopsis:**
` typedef void* cothread_t;  cothread_t co_active(); cothread_t co_create(unsigned int heapsize, void (*coentry)(void)); void       co_delete(cothread_t cothread); void       co_switch(cothread_t cothread);`

------------------------------------------------------------------------

**Usage:**

------------------------------------------------------------------------

`typedef void* cothread_t;`
Handle to cothread.
Handle must be of type void\*.
A value of null (0) indicates an uninitialized or invalid handle, whereas a non-zero value indicates a valid handle.

------------------------------------------------------------------------

`cothread_t co_active();`
Return handle to current cothread. Always returns a valid handle, even when called from the main program thread.

------------------------------------------------------------------------

`cothread_t co_create(unsigned int heapsize, void (*coentry)(void));`
Create new cothread.
Heapsize is the amount of memory allocated for the cothread stack, specified in bytes. This is unfortunately impossible to make fully portable. It is recommended to specify sizes using \`n \* sizeof(void\*)’. It is better to err on the side of caution and allocate more memory than will be needed to ensure compatibility with other platforms, within reason.
