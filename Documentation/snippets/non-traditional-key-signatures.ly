%% DO NOT EDIT this file manually; it is automatically
%% generated from LSR http://lsr.dsi.unimi.it
%% Make any changes in LSR itself, or in Documentation/snippets/new/ ,
%% and then run scripts/auxiliar/makelsr.py
%%
%% This file is in the public domain.
\version "2.14.2"

\header {
  lsrtags = "version-specific, really-cool, pitches, contemporary-notation, staff-notation"

%% Translation of GIT committish: b482c3e5b56c3841a88d957e0ca12964bd3e64fa
  doctitlees = "Armaduras de tonalidad no tradicionales"
  texidoces = "

La muy utilizada instrucción @code{\\key} establece la propiedad
@code{keySignature} property, dentro del contexto @code{Staff}.

Para crear armaduras de tonalidad no estándar, ajuste esta
propiedad directamente.  El formato de esta instrucción es una
lista:

@code{\\set Staff.keySignature = #`(((octava . paso) . alteración)
((octava . paso) . alteración) ...)} donde, para cada elemento
dentro de la lista, @code{octava} especifica la octava
(siendo@tie{}cero la octava desde el Do@tie{}central hasta el Si
por encima), @code{paso} especifica la nota dentro de la octava
(cero@tie{}significa@tie{}Do y 6@tie{}significa@tie{}Si), y
@code{alteración} es @code{,SHARP ,FLAT ,DOUBLE-SHARP}
etc. (observe la coma precedente.)

De forma alternativa, para cada elemento de la lista el uso del
formato más conciso @code{(paso . alteración)} especifica que la
misma alteración debe estar en todas las octavas.

He aquí un ejemplo de una posible armadura para generar una escala
exátona:
"


%% Translation of GIT committish: d76b338302374164acc9b62a0d628d4d230bfa95
  texidocit = "
Il comando @code{\\key} comunemente usato imposta la proprietà
@code{keySignature}, che fa parte del contesto @code{Staff}.

Per creare armature di chiave non standard, tale proprietà va
impostata esplicitamente.  Il formato di questo comando è
una lista:

@code{\\set Staff.keySignature = #`(((ottava . grado) . alterazione) ((ottava
. grado) . alterazione) ...)} dove, per ogni elemento della lista,
@code{ottava} indica l'ottava (0 è l'ottava dal Do centrale
al Si precedente), @code{grado} indica la nota all'interno
dell'ottava (0 significa Do e 6 significa Si) e @code{alterazione}
può essere @code{,SHARP ,FLAT ,DOUBLE-SHARP} etc.  (Si noti la virgola iniziale.)
Le alterazioni nell'armatura di chiave appariranno nell'ordine inverso
a quello in cui sono sono specificate.

Altrimenti, usando, per ogni elemento della lista, il formato breve
@code{(grado . alterazione)}, ciò indica che la stessa alterazione deve
essere presente in tutte le ottave.

Per le scale microtonali in cui un @qq{diesis} non equivale a cento centesimi, @code{alter}
si riferisce all'alterazione come a una proporzione di un duecentesimo di tono intero.

Ecco un esempio di una possibile armatura per generare una scala
a tono intero:
"
  doctitleit = "Armature di chiave non tradizionali"

%% Translation of GIT committish: 0a868be38a775ecb1ef935b079000cebbc64de40
  doctitlede = "Untypische Tonarten"
  texidocde = "
Der üblicherweise benutzte @code{\\key}-Befehl setzt die
@code{keySignature}-Eigenschaft im @code{Staff}-Kontext.

Um untypische Tonartenvorzeichen zu erstellen, muss man diese Eigenschaft
direkt setzen.  Das Format für den Befehl ist eine Liste: @code{ \\set
Staff.keySignature = #`(((Oktave . Schritt) . Alteration) ((Oktave
. Schritt) . Alteration) ...)} wobei für jedes Element in der Liste
@code{Oktave} die Oktave angibt (0@tie{}ist die Oktave vom
eingestrichenen@tie{}C bis zum eingestrichenen@tie{}H), @code{Schritt} gibt
die Note innerhalb der Oktave an (0@tie{}heißt@tie{}C und
6@tie{}heißt@tie{}H), und @code{Alteration} ist @code{,SHARP ,FLAT
,DOUBLE-SHARP} usw.  (Beachte das beginnende Komma.)

Alternativ kann auch jedes Element der Liste mit dem allgemeineren Format
@code{(Schritt . Alteration)} gesetzt werden, wobei dann die Einstellungen
für alle Oktaven gelten.

Hier ein Beispiel einer möglichen Tonart für eine Ganztonleiter:
"

%% Translation of GIT committish: 3b125956b08d27ef39cd48bfa3a2f1e1bb2ae8b4
  texidocfr = "
La commande @code{\\key} détermine la propriété @code{keySignature} d'un
contexte @code{Staff}.

Des armures inhabituelles peuvent être spécifiées en modifiant
directement cette propriété. Il s'agit en l'occurence de définir une
liste@tie{}:

@code{\\set Staff.keySignature = #`(((octave . pas) . altération) ((octave
. pas) . altération) @dots{})}

dans laquelle, et pour chaque élément,
@code{octave} spécifie l'octave (0@tie{}pour celle allant du
do@tie{}médium au si supérieur), @code{pas} la note dans cette octave
(0@tie{}pour@tie{}do et 6@tie{}pour@tie{}si), et @code{altération} sera
@code{,SHARP ,FLAT ,DOUBLE-SHARP} etc.  (attention à la virgule en
préfixe).

Une formulation abrégée -- @code{(pas . altération)} -- signifie que
l'altération de l'élément en question sera valide quel que soit l'octave.


Voici, par exemple, comment générer une gamme par ton :

"
  doctitlefr = "Armures inhabituelles"


  texidoc = "
The commonly used @code{\\key} command sets the @code{keySignature}
property, in the @code{Staff} context.

To create non-standard key signatures, set this property directly. The
format of this command is a list:

@code{ \\set Staff.keySignature = #`(((octave . step) . alter) ((octave
. step) . alter) ...) } where, for each element in the list,
@code{octave} specifies the octave (0 being the octave from middle C to
the B above), @code{step} specifies the note within the octave (0 means
C and 6 means B), and @code{alter} is @code{,SHARP ,FLAT ,DOUBLE-SHARP}
etc. (Note the leading comma.) The accidentals in the key signature
will appear in the reverse order to that in which they are specified.


Alternatively, for each item in the list, using the more concise format
@code{(step . alter)} specifies that the same alteration should hold in
all octaves.


For microtonal scales where a @qq{sharp} is not 100 cents, @code{alter}
refers to the alteration as a proportion of a 200-cent whole tone.


Here is an example of a possible key signature for generating a
whole-tone scale:

"
  doctitle = "Non-traditional key signatures"
} % begin verbatim


\relative c' {
  \set Staff.keySignature = #`(((0 . 6) . ,FLAT)
                               ((0 . 5) . ,FLAT)
                               ((0 . 3) . ,SHARP))
  c4 d e fis
  aes4 bes c2
}

