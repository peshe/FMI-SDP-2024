Инструкции за употреба:
1. Включете `DynArrayBool.inl` на подходящо място в `DynArray.hpp` от лекциите (примерно веднага след `DynArray.inl`
https://github.com/peshe/FMI-SDP-2024/blob/926454bdac468089b51f90b7db291400166a84db/%D0%9B%D0%B5%D0%BA%D1%86%D0%B8%D0%B8/%D0%BF%D1%80%D0%B8%D0%BC%D0%B5%D1%80%D0%B8/%D0%BB%D0%B8%D0%BD%D0%B5%D0%B9%D0%BD%D0%B8%20%D0%A1%D0%94/DynamicArray/DynArray.hpp#L140
). За най-удобно, може да си преместите локално целия код в
една директория.
4. Използвайте специализацията, като включите `DynArray.hpp` в cpp файл и използвате директно типа
`DynArrayBool`. Забележете, че `DynArray<bool>` няма да сработи, понеже алокаторът по подразбиране
ще връща макиви от `bool`, а кодът в специализацията работи с масиви от `char`, чиито елементи
заемат само по 1 байт. Ако целият код е в една директория, може да изпълните включените тестове,
като компилирате `test.cpp`.
5. Неконстантният `operator []` не е имплементиран тук, но ако искате да видите как се прави,
погледнете
https://github.com/peshe/FMI-SDP-2024/blob/926454bdac468089b51f90b7db291400166a84db/%D0%A1%D0%B5%D0%BC%D0%B8%D0%BD%D0%B0%D1%80%D0%B8/%D0%9A%D0%BE%D0%BC%D0%BF%D1%8E%D1%82%D1%8A%D1%80%D0%BD%D0%B8%20%D0%BD%D0%B0%D1%83%D0%BA%D0%B8/%D0%93%D1%80%D1%83%D0%BF%D0%B0%202/Week_03/boolvector.hpp#L10-L24
(с много малко модификации можете и да копирате `BoolVectorProxy` в тялото на
`DynArray<bool, Allocator>` и съответно имплементацията на неконстантния `operator[]`
https://github.com/peshe/FMI-SDP-2024/blob/926454bdac468089b51f90b7db291400166a84db/%D0%A1%D0%B5%D0%BC%D0%B8%D0%BD%D0%B0%D1%80%D0%B8/%D0%9A%D0%BE%D0%BC%D0%BF%D1%8E%D1%82%D1%8A%D1%80%D0%BD%D0%B8%20%D0%BD%D0%B0%D1%83%D0%BA%D0%B8/%D0%93%D1%80%D1%83%D0%BF%D0%B0%202/Week_03/boolvector.hpp#L33
в https://github.com/peshe/FMI-SDP-2024/blob/e9de7bf4ab141642f78c69defec2903f2b2965e9/%D0%9F%D1%80%D0%B0%D0%BA%D1%82%D0%B8%D0%BA%D1%83%D0%BC/%D0%9E%D0%B1%D1%89%D0%B8/%D0%A1%D0%B5%D0%B4%D0%BC%D0%B8%D1%86%D0%B0_02/solutions/task_01/DynArrayBool.inl#L373-L378
). После можете да разкоментирате съответния ред в `test.cpp`
https://github.com/peshe/FMI-SDP-2024/blob/e9de7bf4ab141642f78c69defec2903f2b2965e9/%D0%9F%D1%80%D0%B0%D0%BA%D1%82%D0%B8%D0%BA%D1%83%D0%BC/%D0%9E%D0%B1%D1%89%D0%B8/%D0%A1%D0%B5%D0%B4%D0%BC%D0%B8%D1%86%D0%B0_02/solutions/task_01/test.cpp#L24.
