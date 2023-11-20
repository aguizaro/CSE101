//-----------------------------------------------------------------------------
// DictionaryTest.cpp by Antonio Guizar Orozco
// PA7
// CruzID: aguizaro
//
// Test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include"Dictionary.h"

int main(){
        std::string keys[] =   {
                    "a",
                    "widen",
                    "accomplished",
                    "crooning",
                    "admissions",
                    "aghas",
                    "alkali",
                    "heartsease",
                    "herods",
                    "historifying",
                    "hopdog",
                    "hurds",
                    "ammunitions",
                    "waltham",
                    "weirder",
                    "woolded",
                    "yarmulkas",
                    "animality",
                    "anything",
                    "arbitrage",
                    "arundel",
                    "atoll",
                    "aviates",
                    "bakestones",
                    "barricoes",
                    "beefburgers",
                    "bespatters",
                    "birder",
                    "blowzy",
                    "cocoonery",
                    "borderlines",
                    "breakfast",
                    "bucellas",
                    "buttonmould",
                    "cambist",
                    "caramelizing",
                    "catafalco",
                    "centums",
                    "chassidic",
                    "chivvies",
                    "cinerarias",
                    "clerkdoms",
                    "comedo",
                    "conceptionists",
                    "consecrated",
                    "conversant",
                    "corruptest",
                    "cozing",
                    "curia",
                    "damfool",
                    "decembrist",
                    "defroze",
                    "denigrator",
                    "designatory",
                    "dialyzing",
                    "diphtheroid",
                    "disentwined",
                    "disseverance",
                    "dollar",
                    "dramatize",
                    "dupions",
                    "edale",
                    "elites",
                    "encaging",
                    "enshrinements",
                    "epizoon",
                    "etheric",
                    "exchequers",
                    "exsiccant",
                    "fanaticise",
                    "feoffed",
                    "finns",
                    "flocks",
                    "foreboder",
                    "frailties",
                    "fulas",
                    "gambade",
                    "gemmative",
                    "gimleting",
                    "gnomonic",
                    "grammes",
                    "grotesque",
                    "gyrocar",
                    "haqueton",
                    "hypothecated",
                    "immasculinity",
                    "inaccurate",
                    "indifferentists",
                    "inhabitation",
                    "insurgents",
                    "intil",
                    "irrepealable",
                    "jargonelles",
                    "judaic",
                    "kens",
                    "knobbers",
                    "lambdas",
                    "lawfulness",
                    "leucoderma",
                    "liposuction",
                    "longanimity",
                    "luters",
                    "majorcan",
                    "marblers",
                    "mattering",
                    "melville",
                    "methody",
                    "mimsy",
                    "mislikings",
                    "tulbans",
                    "molehill",
                    "moralization",
                    "nickeled",
                    "mulled",
                    "myrmecophiles",
                    "necrophiliacs",
                    "nord",
                    "oarsmanship",
                    "offbeat",
                    "oppignorate",
                    "osteology",
                    "ovariotomy",
                    "overstrewing",
                    "palimonies",
                    "parallelepipedon",
                    "pasticcio",
                    "peghed",
                    "pettling",
                    "phrenologized",
                    "pionic",
                    "pledgors",
                    "pollinates",
                    "portlier",
                    "precipitate",
                    "presupposing",
                    "prognosticate",
                    "protonemata",
                    "pulmonary",
                    "qanat",
                    "quizzified",
                    "rantipoling",
                    "rebores",
                    "rediffusion",
                    "reincarnated",
                    "reordains",
                    "resonate",
                    "reviewals",
                    "ringhals",
                    "rosewoods",
                    "rusticises",
                    "samariform",
                    "saxaul",
                    "scirrhuses",
                    "scutched",
                    "seminars",
                    "sever",
                    "shining",
                    "siftings",
                    "skald",
                    "peridinian",
                    "sloganise",
                    "snoods",
                    "sonant",
                    "spatular",
                    "splenium",
                    "st",
                    "stembucks",
                    "stormbound",
                    "stuprated",
                    "subtacks",
                    "supercalender",
                    "sutile",
                    "synchronisation",
                    "tallyho",
                    "teacake",
                    "tentativeness",
                    "thenars",
                    "thummim",
                    "toeclips",
                    "touter",
                    "trapanning",
                    "tripled",
                    "tyrol",
                    "unbribable",
                    "underdraining",
                    "unfearfully",
                    "universalness",
                    "unpowdered",
                    "unsluiced",
                    "unweldability",
                    "usucapting",
                    "veer",
                    "vicars",
                    "vltava",
                    "zircaloys"    
                  };

    Dictionary A;
    A.setValue("Ant", 32);
    A.setValue("Box", 35);
    A.setValue("Cat", 39);
    A.setValue("Ant", 30);
    A.setValue("Byte", 8);
    A.setValue("Cup", 90);
    A.setValue("Court", 390);
    A.setValue("Abe", 87);
    A.setValue("After", -120);

    (A.contains("Ant")) ? std::cout << "A contains key: \"Ant\" and has value: " << A.getValue("Ant"): std::cout << "A does NOT contains key: \"Ant\"";
    std::cout << std::endl;
    (A.contains("Cat")) ? std::cout << "A contains key: \"Cat\" and has value: " << A.getValue("Cat"): std::cout << "A does NOT contains key: \"Cat\"";
    std::cout << std::endl;
    std::cout << A << std:: endl;
    A.clear();
    std::cout << "A size: " << A.size() << std::endl;
    std::cout << A << std:: endl;

    Dictionary B;
    B.setValue("Cat", 2);
    B.setValue("Box", 3);
    B.setValue("Ant", 1);

    Dictionary C;
    C.setValue("Ant", 1);
    C.setValue("Box", 3);
    C.setValue("Cat", 2);

    std::string delim= "";
    for(B.begin(); B.hasCurrent(); B.next()){
        std::cout << delim << B.currentKey() << ": " << B.currentVal();
        delim= ", ";
    }
    std::cout << std::endl;
    delim= "";
    for(B.end(); B.hasCurrent(); B.prev()){
        std::cout << delim << B.currentKey() << ": " << B.currentVal();
        delim= ", ";
    }

    std::cout << std::endl;
    (B == C) ? std::cout << "TRUE" <<std::endl: std::cout << "FALSE" <<std::endl;

    Dictionary D(C);
    (D == C) ? std::cout << "TRUE" <<std::endl: std::cout << "FALSE" <<std::endl;
    (D.pre_string() == C.pre_string())? std::cout << "TRUE" <<std::endl: std::cout << "FALSE" <<std::endl;

    A= C;
    (A.pre_string() == C.pre_string())? std::cout << "TRUE" <<std::endl: std::cout << "FALSE" <<std::endl;
    (A == C) ? std::cout << "TRUE" <<std::endl: std::cout << "FALSE" <<std::endl;

    //A.clear();
    for (int i= 65; i<=90; i++){
        std::string s= ""; s+= char(i);
        A.setValue(s , i*5);
    }
    A.setValue("B", 100);

    std::cout << std::endl;
    A.remove("Ant"); A.remove("Cat"); A.remove("Box");
    std::cout << A << std::endl;
    std::cout << "A size: " << A.size() << std::endl;
                
    Dictionary E;
    for(int i= 0; i<195; i++)
        E.setValue(keys[i], i*2);

    std::cout << E << std::endl;

    std::cout << "Found: \"vicars\" " << E.getValue("vicars") <<std::endl;
    std::cout << "Found: \"atol\" " << E.getValue("atoll") <<std::endl;
    std::cout << "Found: \"st\" " << E.getValue("st") <<std::endl;

    std::cout << std::endl;

    for(E.end(); E.hasCurrent(); E.prev()){
        E.currentVal()= 0;
    }

    std::cout << E << std::endl;

    Dictionary F;
    F= E;
    (F == E) ? std::cout << "TRUE" <<std::endl: std::cout << "FALSE" <<std::endl;

    for(int i= 0; i<195; i++){
        E.end();
        std::cout << "Removing: " << E.currentKey() << std::endl;
        E.remove(E.currentKey());
    }

    std::cout <<"After removals, E size: " << E.size() << std::endl;
    E.clear();

    return (EXIT_SUCCESS);
}

/*
Output of program:

A contains key: "Ant" and has value: 30
A contains key: "Cat" and has value: 39
Abe : 87
After : -120
Ant : 30
Box : 35
Byte : 8
Cat : 39
Court : 390
Cup : 90

A size: 0

Ant: 1, Box: 3, Cat: 2
Cat: 2, Box: 3, Ant: 1
TRUE
TRUE
TRUE
TRUE
TRUE

A : 325
B : 100
C : 335
D : 340
E : 345
F : 350
G : 355
H : 360
I : 365
J : 370
K : 375
L : 380
M : 385
N : 390
O : 395
P : 400
Q : 405
R : 410
S : 415
T : 420
U : 425
V : 430
W : 435
X : 440
Y : 445
Z : 450

A size: 26
a : 0
accomplished : 2
admissions : 4
aghas : 6
alkali : 8
ammunitions : 10
animality : 12
anything : 14
arbitrage : 16
arundel : 18
atoll : 20
aviates : 22
bakestones : 24
barricoes : 26
beefburgers : 28
bespatters : 30
birder : 32
blowzy : 34
borderlines : 36
breakfast : 38
bucellas : 40
buttonmould : 42
cambist : 44
caramelizing : 46
catafalco : 48
centums : 50
chassidic : 52
chivvies : 54
cinerarias : 56
clerkdoms : 58
cocoonery : 60
comedo : 62
conceptionists : 64
consecrated : 66
conversant : 68
corruptest : 70
cozing : 72
crooning : 74
curia : 76
damfool : 78
decembrist : 80
defroze : 82
denigrator : 84
designatory : 86
dialyzing : 88
diphtheroid : 90
disentwined : 92
disseverance : 94
dollar : 96
dramatize : 98
dupions : 100
edale : 102
elites : 104
encaging : 106
enshrinements : 108
epizoon : 110
etheric : 112
exchequers : 114
exsiccant : 116
fanaticise : 118
feoffed : 120
finns : 122
flocks : 124
foreboder : 126
frailties : 128
fulas : 130
gambade : 132
gemmative : 134
gimleting : 136
gnomonic : 138
grammes : 140
grotesque : 142
gyrocar : 144
haqueton : 146
heartsease : 148
herods : 150
historifying : 152
hopdog : 154
hurds : 156
hypothecated : 158
immasculinity : 160
inaccurate : 162
indifferentists : 164
inhabitation : 166
insurgents : 168
intil : 170
irrepealable : 172
jargonelles : 174
judaic : 176
kens : 178
knobbers : 180
lambdas : 182
lawfulness : 184
leucoderma : 186
liposuction : 188
longanimity : 190
luters : 192
majorcan : 194
marblers : 196
mattering : 198
melville : 200
methody : 202
mimsy : 204
mislikings : 206
molehill : 208
moralization : 210
mulled : 212
myrmecophiles : 214
necrophiliacs : 216
nickeled : 218
nord : 220
oarsmanship : 222
offbeat : 224
oppignorate : 226
osteology : 228
ovariotomy : 230
overstrewing : 232
palimonies : 234
parallelepipedon : 236
pasticcio : 238
peghed : 240
peridinian : 242
pettling : 244
phrenologized : 246
pionic : 248
pledgors : 250
pollinates : 252
portlier : 254
precipitate : 256
presupposing : 258
prognosticate : 260
protonemata : 262
pulmonary : 264
qanat : 266
quizzified : 268
rantipoling : 270
rebores : 272
rediffusion : 274
reincarnated : 276
reordains : 278
resonate : 280
reviewals : 282
ringhals : 284
rosewoods : 286
rusticises : 288
samariform : 290
saxaul : 292
scirrhuses : 294
scutched : 296
seminars : 298
sever : 300
shining : 302
siftings : 304
skald : 306
sloganise : 308
snoods : 310
sonant : 312
spatular : 314
splenium : 316
st : 318
stembucks : 320
stormbound : 322
stuprated : 324
subtacks : 326
supercalender : 328
sutile : 330
synchronisation : 332
tallyho : 334
teacake : 336
tentativeness : 338
thenars : 340
thummim : 342
toeclips : 344
touter : 346
trapanning : 348
tripled : 350
tulbans : 352
tyrol : 354
unbribable : 356
underdraining : 358
unfearfully : 360
universalness : 362
unpowdered : 364
unsluiced : 366
unweldability : 368
usucapting : 370
veer : 372
vicars : 374
vltava : 376
waltham : 378
weirder : 380
widen : 382
woolded : 384
yarmulkas : 386
zircaloys : 388

Found: "vicars" 374
Found: "atol" 20
Found: "st" 318

a : 0
accomplished : 0
admissions : 0
aghas : 0
alkali : 0
ammunitions : 0
animality : 0
anything : 0
arbitrage : 0
arundel : 0
atoll : 0
aviates : 0
bakestones : 0
barricoes : 0
beefburgers : 0
bespatters : 0
birder : 0
blowzy : 0
borderlines : 0
breakfast : 0
bucellas : 0
buttonmould : 0
cambist : 0
caramelizing : 0
catafalco : 0
centums : 0
chassidic : 0
chivvies : 0
cinerarias : 0
clerkdoms : 0
cocoonery : 0
comedo : 0
conceptionists : 0
consecrated : 0
conversant : 0
corruptest : 0
cozing : 0
crooning : 0
curia : 0
damfool : 0
decembrist : 0
defroze : 0
denigrator : 0
designatory : 0
dialyzing : 0
diphtheroid : 0
disentwined : 0
disseverance : 0
dollar : 0
dramatize : 0
dupions : 0
edale : 0
elites : 0
encaging : 0
enshrinements : 0
epizoon : 0
etheric : 0
exchequers : 0
exsiccant : 0
fanaticise : 0
feoffed : 0
finns : 0
flocks : 0
foreboder : 0
frailties : 0
fulas : 0
gambade : 0
gemmative : 0
gimleting : 0
gnomonic : 0
grammes : 0
grotesque : 0
gyrocar : 0
haqueton : 0
heartsease : 0
herods : 0
historifying : 0
hopdog : 0
hurds : 0
hypothecated : 0
immasculinity : 0
inaccurate : 0
indifferentists : 0
inhabitation : 0
insurgents : 0
intil : 0
irrepealable : 0
jargonelles : 0
judaic : 0
kens : 0
knobbers : 0
lambdas : 0
lawfulness : 0
leucoderma : 0
liposuction : 0
longanimity : 0
luters : 0
majorcan : 0
marblers : 0
mattering : 0
melville : 0
methody : 0
mimsy : 0
mislikings : 0
molehill : 0
moralization : 0
mulled : 0
myrmecophiles : 0
necrophiliacs : 0
nickeled : 0
nord : 0
oarsmanship : 0
offbeat : 0
oppignorate : 0
osteology : 0
ovariotomy : 0
overstrewing : 0
palimonies : 0
parallelepipedon : 0
pasticcio : 0
peghed : 0
peridinian : 0
pettling : 0
phrenologized : 0
pionic : 0
pledgors : 0
pollinates : 0
portlier : 0
precipitate : 0
presupposing : 0
prognosticate : 0
protonemata : 0
pulmonary : 0
qanat : 0
quizzified : 0
rantipoling : 0
rebores : 0
rediffusion : 0
reincarnated : 0
reordains : 0
resonate : 0
reviewals : 0
ringhals : 0
rosewoods : 0
rusticises : 0
samariform : 0
saxaul : 0
scirrhuses : 0
scutched : 0
seminars : 0
sever : 0
shining : 0
siftings : 0
skald : 0
sloganise : 0
snoods : 0
sonant : 0
spatular : 0
splenium : 0
st : 0
stembucks : 0
stormbound : 0
stuprated : 0
subtacks : 0
supercalender : 0
sutile : 0
synchronisation : 0
tallyho : 0
teacake : 0
tentativeness : 0
thenars : 0
thummim : 0
toeclips : 0
touter : 0
trapanning : 0
tripled : 0
tulbans : 0
tyrol : 0
unbribable : 0
underdraining : 0
unfearfully : 0
universalness : 0
unpowdered : 0
unsluiced : 0
unweldability : 0
usucapting : 0
veer : 0
vicars : 0
vltava : 0
waltham : 0
weirder : 0
widen : 0
woolded : 0
yarmulkas : 0
zircaloys : 0

TRUE
Removing: zircaloys
Removing: yarmulkas
Removing: woolded
Removing: widen
Removing: weirder
Removing: waltham
Removing: vltava
Removing: vicars
Removing: veer
Removing: usucapting
Removing: unweldability
Removing: unsluiced
Removing: unpowdered
Removing: universalness
Removing: unfearfully
Removing: underdraining
Removing: unbribable
Removing: tyrol
Removing: tulbans
Removing: tripled
Removing: trapanning
Removing: touter
Removing: toeclips
Removing: thummim
Removing: thenars
Removing: tentativeness
Removing: teacake
Removing: tallyho
Removing: synchronisation
Removing: sutile
Removing: supercalender
Removing: subtacks
Removing: stuprated
Removing: stormbound
Removing: stembucks
Removing: st
Removing: splenium
Removing: spatular
Removing: sonant
Removing: snoods
Removing: sloganise
Removing: skald
Removing: siftings
Removing: shining
Removing: sever
Removing: seminars
Removing: scutched
Removing: scirrhuses
Removing: saxaul
Removing: samariform
Removing: rusticises
Removing: rosewoods
Removing: ringhals
Removing: reviewals
Removing: resonate
Removing: reordains
Removing: reincarnated
Removing: rediffusion
Removing: rebores
Removing: rantipoling
Removing: quizzified
Removing: qanat
Removing: pulmonary
Removing: protonemata
Removing: prognosticate
Removing: presupposing
Removing: precipitate
Removing: portlier
Removing: pollinates
Removing: pledgors
Removing: pionic
Removing: phrenologized
Removing: pettling
Removing: peridinian
Removing: peghed
Removing: pasticcio
Removing: parallelepipedon
Removing: palimonies
Removing: overstrewing
Removing: ovariotomy
Removing: osteology
Removing: oppignorate
Removing: offbeat
Removing: oarsmanship
Removing: nord
Removing: nickeled
Removing: necrophiliacs
Removing: myrmecophiles
Removing: mulled
Removing: moralization
Removing: molehill
Removing: mislikings
Removing: mimsy
Removing: methody
Removing: melville
Removing: mattering
Removing: marblers
Removing: majorcan
Removing: luters
Removing: longanimity
Removing: liposuction
Removing: leucoderma
Removing: lawfulness
Removing: lambdas
Removing: knobbers
Removing: kens
Removing: judaic
Removing: jargonelles
Removing: irrepealable
Removing: intil
Removing: insurgents
Removing: inhabitation
Removing: indifferentists
Removing: inaccurate
Removing: immasculinity
Removing: hypothecated
Removing: hurds
Removing: hopdog
Removing: historifying
Removing: herods
Removing: heartsease
Removing: haqueton
Removing: gyrocar
Removing: grotesque
Removing: grammes
Removing: gnomonic
Removing: gimleting
Removing: gemmative
Removing: gambade
Removing: fulas
Removing: frailties
Removing: foreboder
Removing: flocks
Removing: finns
Removing: feoffed
Removing: fanaticise
Removing: exsiccant
Removing: exchequers
Removing: etheric
Removing: epizoon
Removing: enshrinements
Removing: encaging
Removing: elites
Removing: edale
Removing: dupions
Removing: dramatize
Removing: dollar
Removing: disseverance
Removing: disentwined
Removing: diphtheroid
Removing: dialyzing
Removing: designatory
Removing: denigrator
Removing: defroze
Removing: decembrist
Removing: damfool
Removing: curia
Removing: crooning
Removing: cozing
Removing: corruptest
Removing: conversant
Removing: consecrated
Removing: conceptionists
Removing: comedo
Removing: cocoonery
Removing: clerkdoms
Removing: cinerarias
Removing: chivvies
Removing: chassidic
Removing: centums
Removing: catafalco
Removing: caramelizing
Removing: cambist
Removing: buttonmould
Removing: bucellas
Removing: breakfast
Removing: borderlines
Removing: blowzy
Removing: birder
Removing: bespatters
Removing: beefburgers
Removing: barricoes
Removing: bakestones
Removing: aviates
Removing: atoll
Removing: arundel
Removing: arbitrage
Removing: anything
Removing: animality
Removing: ammunitions
Removing: alkali
Removing: aghas
Removing: admissions
Removing: accomplished
Removing: a
After removals, E size: 0
*/