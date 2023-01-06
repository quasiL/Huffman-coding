## Huffmanovo kódování
Huffmanovo kódování je algoritmus využívaný pro bezeztrátovou kompresi dat. Konvertuje znaky vstupního souboru do bitových řetězců různé délky. Znaky, které se ve vstupním souboru vyskytují nejčastěji, jsou konvertovány do bitových řetězců s nejkratší délkou (nejfrekventovanější znak tak může být konvertován do jediného bitu), zatímco znaky, které se vyskytují velmi zřídka, jsou konvertovány do delších řetězců (mohou být i delší než 8 bitů). 

## Popis
Huffmanův algoritmus je technika pro kompresi a dekompresi dat. Funguje tak, že sestrojí binární strom, ve kterém uzly představují znaky v datech a frekvence každého znaku je zakódována ve váze odpovídajícího uzlu.

Podrobný popis Huffmanova algoritmu:

1. Pro každý znak vytvořit listový uzel a každému uzlu přiřaďit hodnotu frekvence na základě toho, kolikrát se znak objevil v datech.
2. Vytvořit nový vnitřní uzel s frekvencí rovnou součtu frekvencí jeho potomků. Udělat ze dvou uzlů s nejmenšími frekvencemi potomky tohoto nového uzlu.
3. Opakovat předchozí krok, dokud nezůstane pouze jeden uzel, což je kořenový uzel stromu.
4. Přiřadit bit "0" každé hraně vedoucí k levému potomkovi a bit "1" každé hraně vedoucí k pravému dítěti. Tyto bity představují cestu od kořene ke každému listovému uzlu a tvoří kódové slovo pro každý znak.
5. Chcete-li komprimovat data, nahraďte každý znak v původních datech jeho kódovým slovem.
6. Chcete-li data dekomprimovat, projděte strom pomocí kódových slov a dekódujte původní znaky.

Všechny kroky algoritmu jsou implementovány ve třídě `huffman`.
Vlakna se používají podle principu consumer-producent (třída `lines_queue`).

## Návod
`./huffman_coding --help`
