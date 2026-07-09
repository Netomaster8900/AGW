


# <img width="110" height="110" alt="a (2)" src="https://github.com/user-attachments/assets/e9752bb6-a743-4120-9ed6-238f3888cff3" /> AGW
AGW, del ingles Advanced Graphics Wrapper, como dice su nombre, es una coleccion de abstracciones graficas para windows, el
cual permite, entre otras cosas, dibujar con una tasa extremadamente alta de rendimiento, por la simplicidad de cada escritura a
la salida de video, mientras permite seleccionar qué módulos internos se usarán, permitiendo anular por completo el peso de los
módulos que no se ajusten a las necesidades del proyecto

## Características
si bien, es exclusivo para Windows, por la facilidad del mismo sistema para desarrollo, y su núcleo se basa en GDI, se han logrado
mediciones excelentes en procesadores modestos, como por ejemplo, un I7 6600U (el procesador donde trabajo)

en esta tabla se listan todos los tiempos de renderizado a distintas resoluciones, sobre un solo núcleo del 6600U, bajo MSVC en debug
|Reloj|resolucion|tiempo(ms)|
|:-----:|:----------:|:----------:|
|1.87GHz|1920*1080|~6ms|
|1.12GHz|1280*720|~3ms|
|1.18GHz|800*600|~2ms|

esto medido según reiteradas pruebas de trabajo durante el desarrollo y utilización de la API en proyectos propios, donde alcanzó un
rendimiento límite, de 3Gpix/s con todo el CPU a 3.32GHz

## Recomendaciones
Este software está diseñado para usarse sobre Visual Studio 2022 por particularidades de la sintaxis

Se recomienda seguir al pie de la letra las indicaciones del manual de usuario para empezar a usar la API

La API se diseñó específicamente para Windows Vista o superiores

## Particularidades
Si bien esta pieza de Software está probada y se reitera su excepcional rendimiento, se recuerda que todo trabaja sobre CPU aún, por lo
que cualquier actualización en la GPU no provocará absolutamente ningún cambio en el rendimiento si no se actualiza el CPU

absolutamente toda la API es monolítica, y en su mayoría es imposible de separar en módulos bien definidos al corto plazo, por
lo que no se planea hacerlo

## Notas:
es necesario tener a SDL2, si se usa la macro correspondiente, fuera de la carpeta estándar(SDL/SDL2), o en su lugar, cambiar la ruta
de inclusión que se usa dentro del código
