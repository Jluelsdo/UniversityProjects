# Designentscheidungen SEKM

## Fragen, die aufgekommen sind:
1. Wie entscheiden wir, ob eine fehlerhafte Verbindugnsanfrage zurueckgewiesen wird, oder eine entsprechende Loesung versucht wird? --> **Loesung: methode in der ConnectUnit (siehe 9.)**

2. Wenn die MPK abstuerzt, ist dann alles weg? Wird etwas persistiert? --> **Waehrend der Laufzeit angelegte Channels werden in der Configdatei persistiert.
Es gibt eine Methode "persistChannel()", die die aktuelle Channelconfiguration in der Configdatei speichert.**

ZU 2.: _**Merke: ein Logger ist ein "Beiprodukt" eines Channels. Somit werden bei persistChannel auch Loggerrelevante Daten persistiert.**_

3. Wenn die MPK hochfaehrt, erstellt sie dann schon vordefineirte Channels? Wenn ja, was fuer welche? --> **Es kann vordefinierte Channels in der Configdatei geben (z.B Haendisch eingetragen). Diese werden dann beim Hochfahren erstellt.**

4. Wie machen wir die Sache mit den IDs jetzt mit Logger und Channel?

## Entscheidungen/So haben wirs verstanden:
1. Die MPK faehrt hoch und es werden Channels angelegt. Wenn die MPK jetzt abstuerzt, dann sind die erstellten Kanaele in der Config-Datei (oder Klasse??) aufgelistet worden. Beim naechsten Hochfahren der MPK werden diese gemerkten Kanaele dann automatisch erstellt.

2. Da wir pro Channel genau einen Logger haben, wird beim Anlegen eines Channels automatisch ein Logger mit angelegt.

3. Damit die Uebersicht beibehalten wird, werden fuer Logger und Channel separate Klassen erstellt. Diese resultieren dann aus den Configdateien. Gleichzeitig werden in den Configdateien die waehrend der Laufzeit vorliegenden Klassen persistiert.

4. Um ein Rekonfigurieren zu vereinfachen, gibt es eine zentrale Configdatei mit Informationen zu Logger und Channel.

5. Die Config-Datei wird als default erstellt. NICHT wie bisher dynamisch eingesetzt, sondern mit static Config werten einmalig gefüllt.

6. Wir gehen mit der Software davon aus, dass sie moeglichst defensiv umgesetzt ist.

7. Dynamische aenderungen an der Config-Datei sind nur ueber die Initialization -> InitUnit -> reinitChannel() möglich.

8. Eine Reinitialisierung wird vom Sender (und NICHT vom Empfaenger) initiiert ist spezifisch fuer einen Kanal durchfuehrbar.

9. In der Configdatei ist ein parameter fuer die Channels vorhanden der definiert, wie diese sich gemaeß Tag C2a (siehe: https://ilias.th-koeln.de/goto.php?target=file_2353837_download&client_id=ILIAS_FH_Koeln) verhalten sollten.

10. Daten der Message Queue werden nicht in der Configdatei persistiert nicht.

11. Die Methode Initialization -> InitUnit -> initChannel() initialisiert (aus unserer Logik heraus) auch den Logger mit.

12. Jeder Logger hat dieselbe ID wie sein channel