# Designentscheidungen SEKM 

## Designentscheidungen Channel
- Channels werden n:1 realisiert. Für n:n werden n*n:1 Chanel mit dem selben Namen erstellt
- FIFO der Massagequeue muss Mulitthreadingfähig sein (Locking)
- Reinitialsierung eines Kanals: Parallel zu bestehenden Kanal

## Designentscheidungen Sender
- Der Sender holt sich von der MPK seinen Namen (Um zu wissen auf welchen Channel er subscribed ist)
- Zwischen Sender und Channel wird eine Fassade instaliert (kein Proxy)

## Designentscheidungen Empfänger
- Es wird ein Proxy zwischen Empfänger und Chanel angelegt

## Designentscheidungen Logger
- Beim Senden und Emfangen wird geloggt
- Watchdog --> gitb's aber nur wenn der channel aktiv ist
- Daten werden geloggt, aber natürlich in der Sprache des Senders (Die sprichst du evtl nicht)
- Einfach in ne txt zb 3 mb schreiben und danach wieder oben anfangen und einfach überschreiben
- Geh' in jedem Fall davon aus, dass der Rechner performant gut genug ist um auch zu loggen logging soll aktiv (eigener thread of execution) gestaltet werden
- --> möglichst vermeiden, dass das schreiben zu lange dauert
- Beim Stromausfall muss alles gespeichert werden.(Stichwort Backup Batterie)
- Das Altern von Nachrichten ist anwendungsspezifisch und wir können nichts dagegen machen mit unserer MPK
- Machen Sie doch mal ein Use-Case Diagramm und überlegen sich best- und worst-case aus <-- kann die Architektur das stemmen?
- Da mehrere Channels existieren und diese in derselben Datei schreiben, muss der Logger locking implementiere (LogPersistService)
- Zwischen dem Logger und dem Channel ist nichts


## Weitere Designfragen:
### Warum Active Object bei den channels?:
- Um Multithredding zu unterstützen und damit die sich nicht untereinenader stören. (Stichwort: Independancy)

### Warum ist die ConnectUnit Singleton?
- Da sie eine "Managing" Rolle übernimmt, darf es nur eine davon geben!

### Warum ConnectionAdapter? (Mit sender und receiver)
- Damit der Sender und Empfänger über diese Stelle an das Active Object kommen
	------------Notiz: Das Active Object selbst ist im Channel. Also jeder Channel hat ein Active Object

- Für Multicast!! Es sollen verschiedene Überstezungen jedem einzelnen Receiver zuordbar sein. Über ConnAdapterReceiver sollen individuelle Proxypfade verfügbar sein. (Die uid in der Oberklasse "ConnectionAdapter" soll die ID des receivers (bzw. Senders) sein. Diese wird evtl. interessant, wenn man aus einer Mulitcast Verbindung einzelne Receiver rausnehmen möchte)

- Alternative war: Callback function. Das machen wir aber nicht, weil das die Komplexität heben würde und wir dadurch keinen signifikanten Mehrwert bekommen.

### Sind unsere Channels aktiv oder passiv?

### Sind unsere Logger aktiv oder passiv?



# Notizen, Fragen:
Connect Unit --> delete insatnce???

Anmerkung: Die externen Sachen sind eig nicht von uns und werden nur für testzwecke erstellt.

ERSTMAL RAUSGENOMMEN (EVTL. SPÄTER NACHHOLEN):
	-Das Löschen eines Kanals (Channel)
	-getKid in der Klasse Channel

## Hinweise von Kreiser (05.12.2022):
- Ordnen sie im Active Object die verschiedenen Klassen der Aufgabe zu

- Channel läuft als passiver im Sender oder Empfänger. Wenn einer der beiden stirbt, dann kommt mean time to repair ins Spiel.
Das wäre dann: Alternativen Empfänger starten (muss die Appkikation machen). Dieser muss sich in der Applikation neu registrieren. Die Daten gehen dabei aber nicht verloren (hatten wir falsch gedacht/verstanden).

- Channel kann nicht im Sender mit drin liegen. Die sind zwar im selben Thread, aber liegen nicht aufeinander.

- Alte Nachriten bleiben drin, werden aber nicht gelesen. <-- Wie alt darf eine Nachricht werden? Das können wir nicht wirklich festlegen.

- Stichworte (Scoped locking): Wir 

- Der Channel ist ne passive Resource. Sie mussen ja nur Daten speichern. Aktionen finden im Thread of executioon statt. Dies kann aktiv sein, muss aber nicht zwingend!

- Publish-Subscriber ist grundsatzlich okay.

- Active Objet ist dafür da, Sachen anzunehmen und dann ist da ein Server der die Sachen ausführt.

- Das Object ist der Servant beim Active Object.
Stichwort - kannst du Senden? Checke das im Runtime!
## Hinweise von Kreiser (05.12.2022) ENDE