# GASATHON

Completing this [course](https://www.udemy.com/course/unreal-engine-5-gas-top-down-rpg/)

The project is organized as a monolithic module with an auxillary editor module and a Codegen module not handled by Unreal utilizing the [gencpp](https://github.com/Ed94/gencpp.git) library.

Implementation design perfs:

* Keep data structures and codepaths flat with minimal abstraction patterns
  * Lift to more specific or generalized code-paths only when necessary
* Keep everything data-wise in the runtime unless there is a measurable performance cost.
* Some exploratory optimizations for educational purposes.
* Plugins are installed in the engine repo unless not possible.
* Code almost exclusively in C++ for everything but cosmetics (this is an engineering portfolio piece).
* Keep static module functions within C++ namesapces and have the in BP function libraries to expose to BPs.
* Perfer stage-metaprogramming to C++ compiler provided templating (when possible).

The repo is also hosted on : [https://git.cozyair.dev/ed/GASATHON](https://git.cozyair.dev/ed/GASATHON)
It should be mirrored here however to latest.
