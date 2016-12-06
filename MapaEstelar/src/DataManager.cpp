#include "DataManager.h"

#include <string>

DataManager::DataManager()
{

}
DataManager::~DataManager()
{

}

std::string DataManager::getName(std::string A)
{
	if (A=="ORI")
		return "Orion";
	else if (A=="GEM")
		return "Gemini";
	else if (A=="CNC")
		return "Cancer";
	else if (A=="CMI")
		return "Canis Minor";
	else if (A=="CMA")
		return "Canis Maior";
	else if (A=="MON")
		return "Monoceros";
	else if (A=="LEP")
		return "Lepus";
	else if (A=="SEX")
		return "Sextans";
	else if (A=="PYX")
		return "Pyxis";
	else if (A=="TRI")
		return "Triangulum";
	else if (A=="ARI")
		return "Aries";
	else if (A=="LEO")
		return "Leo";
	else if (A=="LMI")
		return "Leo Minor";
	else if (A=="LYN")
		return "Lynx";
	else if (A=="VIR")
		return "Virgo";
	else if (A=="VEL")
		return "Vela";
	else if (A=="CEN")
		return "Centaurus";
	else if (A=="CRT")
		return "Crater";
	else if (A=="ANT")
		return "Antlia";
	else if (A=="HYA")
		return "Hydra";
	else if (A=="PUP")
		return "Puppis";
	else if (A=="COL")
		return "Columba";
	else if (A=="CAR")
		return "Carina";
	else if (A=="CAS")
		return "Cassiopeia";
	else if (A=="PIC")
		return "Pictor";
	else if (A=="DOR")
		return "Dorado";
	else if (A=="AND")
		return "Andromeda";
	else if (A=="TAU")
		return "Taurus";
	else if (A=="AUR")
		return "Auriga";
	else if (A=="HOR")
		return "Horologium";
	else if (A=="CAE")
		return "Caelum";
	else if (A=="SCL")
		return "Sculptor";
	else if (A=="CET")
		return "Cetus";
	else if (A=="FOR")
		return "Fornax";
	else if (A=="PHE")
		return "Phoenix";
	else if (A=="CAM")
		return "Camelopardalis";
	else if (A=="ERI")
		return "Eridanus";
	else if (A=="PEG")
		return "Pegasus";
	else if (A=="PER")
		return "Perseus";
	else if (A=="PSC")
		return "Pisces";
	else if (A=="UMA")
		return "Ursa Maior";
	else if (A=="UMI")
		return "Ursa Minor";
	else if (A=="CEP")
		return "Cepheus";
	else if (A=="CHA")
		return "Chameleon";
	else if (A=="CIR")
		return "Circinus";
	else if (A=="COM")
		return "Coma Berenices";
	else if (A=="CRA")
		return "Corona Australis";
	else if (A=="CRB")
		return "Corona Borealis";
	else if (A=="CRU")
		return "Crux";
	else if (A=="CRV")
		return "Corvus";
	else if (A=="CVN")
		return "Canes Venatici";
	else if (A=="CYG")
		return "Cygnus";
	else if (A=="DEL")
		return "Delphinus";
	else if (A=="DRA")
		return "Draco";
	else if (A=="EQU")
		return "Equuleus";
	else if (A=="GRU")
		return "Grus";
	else if (A=="HER")
		return "Hercules";
	else if (A=="HYI")
		return "Hydrus";
	else if (A=="IND")
		return "Indus";
	else if (A=="LAC")
		return "Lacerta";
	else if (A=="LIB")
		return "Libra";
	else if (A=="LUP")
		return "Lupus";
	else if (A=="LYR")
		return "Lyra";
	else if (A=="MEN")
		return "Mensa";
	else if (A=="MIC")
		return "Microscopium";
	else if (A=="MUS")
		return "Musca";
	else if (A=="NOR")
		return "Norma";
	else if (A=="OCT")
		return "Octans";
	else if (A=="OPH")
		return "Ophiuchus";
	else if (A=="PAV")
		return "Pavo";
	else if (A=="PSA")
		return "Piscis Austrinus";
	else if (A=="RET")
		return "Reticulum";
	else if (A=="SCO")
		return "Scorpius";
	else if (A=="SCT")
		return "Scutum";
	else if (A=="SER")
		return "Serpens";
	else if (A=="SGE")
		return "Sagitta";
	else if (A=="SGR")
		return "Sagittarius";
	else if (A=="APS")
		return "Apus";
	else if (A=="AQL")
		return "Aquila";
	else if (A=="AQR")
		return "Aquarius";
	else if (A=="ARA")
		return "Ara";
	else if (A=="VOL")
		return "Volans";
	else if (A=="VUL")
		return "Vulpecula";
	else if (A=="BOO")
		return "Bootes";
	else if (A=="CAP")
		return "Capricornus";
	else if (A=="TUC")
		return "Tucana";
	else if (A=="TRA")
		return "Triangulum Australe";
	else if (A=="TEL")
		return "Telescopium";
	else
		return "Error, check for: "+A;

}

std::string DataManager::getDescription(std::string A)
{
	if (A=="ORI")
		return "Orion, (el Cazador), es una constelacion prominente, quizas la mas conocida del cielo. Sus estrellas brillantes y visibles desde ambos hemisferios hacen que esta constelacion sea reconocida mundialmente. La constelacion es visible a lo largo de toda la noche durante el invierno en el hemisferio norte, verano en hemisferio sur; es asimismo visible pocas horas antes del amanecer desde finales del mes de agosto hasta mediados de noviembre y puede verse en el cielo nocturno hasta mediados de abril. Orion se encuentra cerca de la constelacion del rio Eridanus y apoyado por sus dos perros de caza Canis Maior y Canis Minor peleando con la constelacion del Tauro.";
	else if (A=="GEM")
		return "Gemini (los mellizos) es la tercera constelacion del zodiaco, y se encuentra a unos treinta grados al noroeste de Orion. William Herschel descubrio Urano cerca de eta Geminorum en 1781, y Clyde Tombaugh hizo lo propio con Pluton cerca de delta Geminorum.";
	else if (A=="CNC")
		return "Cancer (el cangrejo), en astronomia, es una de las doce constelaciones del zodiaco. En astrologia, Cancer constituye uno de los doce signos zodiacales. La constelacion de Cancer es pequena y debil. Se encuentra entre las constelaciones de Geminis al este, Lince al norte y las constelaciones de Canis Minor e Hidra al sur.\nLa constelacion tambien da su nombre al tropico de Cancer.";
	else if (A=="CMI")
		return "Canis Minor, en castellano Can Menor (el perro pequeno) es una de las 88 constelaciones modernas. Formo parte tambien de forma evidente de las 48 constelaciones primitivas del Almagesto de Ptlolomeo, dato que se encuentra incluido en la fuente de este ultimo trabajo: la gran obra denominada Astronomica de Manilio de Antioquia. La figura del Can menor es simple: una linea que une dos estrellas. Procyon su estrella mas brillante forma junto con Betelgeuse (Orion) y Sirio (Can Mayor) el \"Triangulo de Invierno\".";
	else if (A=="CMA")
		return "El Can Mayor (Canis Maior) es una constelacion que parece seguir, en su recorrido en el cielo debido al movimiento diurno, al \"Gran Cazador\", Orion.";
	else if (A=="MON")
		return "Monoceros (en griego unicornio) es una constelacion en el cielo nocturno invernal del hemisferio norte, rodeada por Orion al oeste, Geminis al norte, el Can Mayor al sur e Hydra hacia el este. Otras constelaciones limitrofes son el Can Menor, Lepus y Puppis.";
	else if (A=="LEP")
		return "Lepus (la liebre en latin), es una constelacion situada justo al sur de Orion, y posiblemente representa una liebre siendo perseguida por el. Lepus fue una de las 48 constelaciones de Ptolomeo y hoy es una de las 88 constelaciones modernas.\nEsta constelacion no debe ser confundida con Lupus, el lobo.";
	else if (A=="SEX")
		return "Sextans (el Sextante) es una constelacion menor del sur que fue introducida en el siglo XVII por Johannes Hevelius. La introdujo en recuerdo al instrumento que perdio en un incendio. Esta situada entre Leo e Hydra y no es una constelacion particularmente brillante. No hay mitologia asociada a esta constelacion.";
	else if (A=="PYX")
		return "Pyxis o la Brujula es una constelacion pequena y debil del hemisferio celeste meridional. Fue introducida en el siglo XVIII por Nicolas-Louis de Lacaille con el nombre de Pyxis Nautica y se cuenta entre las ochenta y ocho constelaciones modernas. Esta situada cerca de la antigua constelacion de Argo Navis; en el siglo XIX John Herschel sugirio renombrarla Malus, el Mastil, pero la sugerencia no prospero. La Brujula es completamente visible en latitudes mas al sur de los 53 grados norte, siendo febrero y marzo los meses de mejor visibilidad.\nEsta constelacion esta atravesada por la Via Lactea.";
	else if (A=="TRI")
		return "Triangulum (el \"Triangulo\") es una pequena constelacion del norte, cuyas tres estrellas mas brillantes, de tercera y cuarta magnitud, forman un triangulo casi isosceles. Es una de las 88 constelaciones modernas y tambien fue una de las 48 listadas por Ptolomeo. No debe ser confundida con la constelacion austral Triangulum Australe.";
	else if (A=="ARI")
		return "Aries (el carnero) es una de las constelaciones del zodiaco; se encuentra entre las constelaciones de Piscis, al oeste, y Tauro al este.";
	else if (A=="LEO")
		return "Leo (el leon) es una de las constelaciones del zodiaco. Se encuentra entre Cancer y Virgo.";
	else if (A=="LMI")
		return "Leo Minor (latin de Leon Menor) es de las constelaciones mas pequenas: apenas puede ser reconocida como un triangulo y esta situada entre las facilmente reconocibles Osa Mayor y Leo. A diferencia de Leo no pertenece a la antigua lista de 48 constelaciones dibujadas por Ptolomeo en el segundo siglo a. C., sino que fue creada por Johannes Hevelius en 1687.";
	else if (A=="LYN")
		return "Lince (en ingles Lynx) es una constelacion del Hemisferio norte, introducido en el siglo XVII por Johannes Hevelius. El origen del nombre se debe a la poca luminosidad de sus astros, pues se necesita tener ojos de lince para poder verla. Para localizar al Lince hay que buscar entre dos constelaciones muy luminosas, la Osa Mayor y Auriga.";
	else if (A=="VIR")
		return "Virgo (la virgen) es una constelacion del zodiaco. Se encuentra entre Leo al oeste y Libra al este y es una de las constelaciones mas grandes visibles en el cielo.";
	else if (A=="VEL")
		return "Vela es una constelacion austral, una de las cuatro partes en que fue dividida la constelacion de Argo Navis (el navio Argos), siendo las otras Carina (la quilla), Puppis (la popa) y Pyxis (la brujula).";
	else if (A=="CEN")
		return "Centaurus (el centauro), es una extensa constelacion que se encuentra al norte de Crux y en el extremo norte de la Via Lactea. Rodea la Cruz del Sur formando una de las mas ricas y hermosas constelaciones del cielo.";
	else if (A=="CRT")
		return "Crater (taza en Latin) es una de las 88 constelaciones y tambien fue una de las 48 listadas por Ptolomeo. Se dice que representa la copa de Apolo. No tiene estrella con brillo mayor a la cuarta magnitud.";
	else if (A=="ANT")
		return "Antlia o la Bomba Neumatica es una constelacion del hemisferio celeste austral. Su nombre hace referencia al aparato inventado por el fisico frances Denis Papin en el siglo XVII. La constelacion fue introducida por Nicolas-Louis de Lacaille, con el nombre de Antlia Pneumatica, cuando estuvo trabajando en el observatorio del cabo de Buena Esperanza y se cuenta entre las ochenta y ocho constelaciones modernas. Situada cerca de las estrellas que formaban la antigua constelacion de Argo Navis, Antlia es completamente visible desde latitudes mas al sur de los 49 grados norte.";
	else if (A=="HYA")
		return "Hidra es la mas grande de las 88 constelaciones modernas, y fue una de las 48 constelaciones que Ptolomeo registro. No debe ser confundida con Hydrus, constelacion del hemisferio sur de menor tamano.";
	else if (A=="PUP")
		return "Puppis (\"Popa\" en latin) es una constelacion austral. Es la mayor de las tres partes en las que se separo la constelacion Nave Argo.";
	else if (A=="COL")
		return "Columba, Latin para paloma, es una pequena constelacion justo al sur de Canis Major y Lepus. Fue sacada de la constelacion Canis Major por Augustin Royer, en 1679.";
	else if (A=="CAR")
		return "Carina (la quilla), en castellano Quilla, es una constelacion austral que forma parte de la antigua constelacion de Argo Navis (el navio Argo). La Union Astronomica Internacional la dividio en cuatro componentes: Carina (la Quilla), Vela (la Vela), Puppis (la Popa) y Pyxis (el compas o la brujula).";
	else if (A=="CAS")
		return "Casiopea es una de las constelaciones compiladas en el catalogo estelar de Tolomeo, el Almagesto, del siglo II. Facilmente reconocible por sus cinco estrellas brillantes que forman un conocido asterismo del cielo circumpolar boreal.\nCasiopea senala al norte (y a la estrella Polar) apuntando desde sus extremos de la M o W. Tiene al otro lado al Gran Carro de la Osa Mayor.\nAl ser tan facil de reconocer es muy usada para encontrar el norte cuando no es posible utilizar a la Osa Mayor para este proposito, cuando esta no es visible en cielos de latitudes templadas (menos de 35 grados N - Islas Canarias).";
	else if (A=="PIC")
		return "Pictor o el Caballete del Pintor es una constelacion de los cielos australes que se encuentra entre la estrella Canopus y la Gran Nube de Magallanes. Fue creada por el astronomo frances del siglo XVIII Nicolas-Louis de Lacaille con el nombre de Equuleus Pictoris; normalmente se representa con un caballete. La estrella mas brillante de la constelacion es Alfa Pictoris, una estrella blanca de la secuencia principal a unos 97 anos luz de la Tierra. Pictor tambien alberga a RR Pictoris, un sistema de estrellas variables cataclismicas que estallo como nova en 1925, alcanzando una magnitud aparente de 1,2 para desaparecer despues en la oscuridad.";
	else if (A=="DOR")
		return "Dorado es una constelacion austral, creada por Pieter Dirkszoon Keyser y Frederick de Houtman entre 1595 y 1597, y listada por primera vez en la Uranometria de Johann Bayer de 1603; conocida tambien como \"Pez Espada\", recibe su nombre en realidad del dorado delfin o mahi-mahi, Coryphaena hippurus, un pez comestible nativo de America. En ella es visible la mayor parte de la Gran Nube de Magallanes.";
	else if (A=="AND")
		return "Andromeda es una constelacion boreal situada al sur de Casiopea y cerca de Pegaso. Toma su nombre de la doncella Andromeda de la mitologia griega. Comparte una estrella con Pegaso, la estrella blanco-azulada de la esquina noroeste del Cuadrante de Pegaso, denominada Alpheratz o Sirrah.";
	else if (A=="TAU")
		return "Tauro o Taurus es una constelacion zodiacal; su nombre en latin es Taurus y en espanol toro. Destaca en el cielo invernal, entre Aries al oeste y Geminis al este. Al norte se encuentran Perseo y Auriga; al sureste Orion, y al suroeste Eridanus y Cetus.\nEn el zodiaco es el segundo signo. Como tal, en la antigüedad contenia la constelacion del mismo nombre, pero la precesion de los equinoccios ha hecho que el signo de Tauro se encuentre ocupado por la constelacion de Aries. Actualmente el sol brilla sobre Tauro entre el 14 de mayo y el 21 de junio.";
	else if (A=="AUR")
		return "Auriga (el cochero), en castellano Cochero, es una constelacion del hemisferio norte. Su localizacion es facil: basta con mirar por encima de Orion. Se ve un pentagono de estrellas brillantes, entre las que destaca Capella.";
	else if (A=="HOR")
		return "Horologium (el Reloj) es uno de las menores constelaciones del sur (declinacion cerca de -60 grados).\nOriginalmente llamado Horologium Oscillitorium por Nicolas Louis de Lacaille, el nombre de la constelacion ha sido acortado para que sea menos pesado. Horologium Oscillitorium se puso en honor al inventor del reloj de pendulo, Christian Huygens.";
	else if (A=="CAE")
		return "Caelum o el Cincel es una debil constelacion del hemisferio celeste austral introducida por Nicolas-Louis de Lacaille en la decada de los 50 del siglo XVIII con el nombre de Caelum Scalptorium. Se cuenta entre las ochenta y ocho constelaciones modernas. Es la octava constelacion mas pequena y subyace bajo un angulo de alrededor de 0,038 estereorradianes, algo menor que el de Corona Australis.\nDebido a su pequeno tamano y su ubicacion lejos del plano de la Via Lactea, Caelum es una constelacion bastante desolada que contiene pocos objetos de interes.";
	else if (A=="SCL")
		return "Sculptor es una constelacion menor del sur, que fue presentada por Nicolas Louis de Lacaille. Originalmente la llamo 'Estudio de escultor', pero posteriormente, el nombre fue acortado.\nSculptor contiene el polo galactico del sur.";
	else if (A=="CET")
		return "Cetus (la ballena o el monstruo marino) es una constelacion del hemisferio sur, en una region conocida como Agua, cerca de otras constelaciones como Aquarius, Piscis y Eridanus.";
	else if (A=="FOR")
		return "Fornax (el horno) es una constelacion austral que fue introducida por Nicolas Louis de Lacaille bajo el nombre de Fornax Chemica (latin para horno quimico).";
	else if (A=="PHE")
		return "Fenix, (el Fenix) es una constelacion menor del sur, introducida por los navegantes daneses Pieter Dirkszoon Keyser y Frederick de Houtman, y popularizada por el libro Uranometria de Johann Bayer en 1603.\nSolo hay treinta estrellas en toda la constelacion, las cuales tienen un brillo de una magnitud mayor a 5.0.\nLa extension aproximada de la constelacion es -41 grados hasta -57 grados declinacion, y desde 23,5h hasta 2h de ascension recta. Esto significa que es generalmente invisible para cualquiera que viva al norte del paralelo 40 en el Hemisferio Norte, y permanece bajo en el cielo para el que viva al norte del Ecuador. Es facilmente visible desde lugares como Australia, Sudamerica y Sudafrica durante el verano del Hemisferio Sur.\nFenix es asociado con la lluvia de estrellas Fenicidas que ocurre cada 5 de diciembre.";
	else if (A=="CAM")
		return "Camelopardalis, la jirafa, es una gran constelacion del hemisferio norte celeste muy poco conspicua, pues sus estrellas mas brillantes (siete) son solo de magnitud 5. Esta situada entre las constelaciones de Auriga y las dos Osas. El nombre de Camelopardalis proviene de \"camello-leopardo\", nombre que los griegos dieron a la jirafa, ya que pensaban que tenia la cabeza de camello y las manchas de leopardo.\nFue introducida como constelacion por Petrus Plancius y publicada por Jakob Bartsch en 1624 en su libro sobre las constelaciones.";
	else if (A=="ERI")
		return "Eridanus es la sexta constelacion mas grande de las 88 constelaciones modernas. Tambien es una de las 48 constelaciones de Ptolomeo.";
	else if (A=="PEG")
		return "Pegaso (el caballo alado) es una constelacion del norte, que recibe su nombre del Pegaso mitico. Es una de las 88 constelaciones modernas y una de las 48 inicialmente descritas por Ptolomeo.";
	else if (A=="PER")
		return "Perseo es una constelacion del norte y representa a Perseo, heroe mitologico que decapito a Medusa. Es una de las 48 constelaciones de Ptolomeo asi como una de las 88 constelaciones modernas. En ella esta la famosa variable Algol, y en ella se localiza la lluvia de meteoros de las perseidas.";
	else if (A=="PSC")
		return "Pisces (los peces) es una constelacion del zodiaco ubicada entre Aquarius al oeste y Aries hacia el este.";
	else if (A=="UMA")
		return "La Osa Mayor (en latin, Ursa Major; abreviado, UMa), tambien conocida como el Carro Mayor, es una constelacion visible durante todo el ano en el hemisferio norte. Entre los aficionados se le conoce con el nombre de \"el carro\", por la forma que dibujan sus siete estrellas principales, aunque ha recibido otros muchos nombres.";
	else if (A=="UMI")
		return "La Osa Menor, ursa en latin, es una constelacion del hemisferio norte. Comparte el mismo nombre que la Osa Mayor, debido a que su cola se asemeja al mango de una cuchara: consta de siete estrellas con la forma de carro; cuatro de ellas forman lo que es la parte honda del carro y las otras tres son el mango del carro. Fue una de las 48 constelaciones enumeradas originalmente por el astronomo Claudio Ptolomeo en el siglo II, y desde entonces forma parte de las 88 constelaciones contemporaneas.\nEl elemento mas conocido de la Osa Menor es la estrella Polar, la cual se encuentra situada aproximadamente en la prolongacion del eje de la Tierra, de modo que permanece casi fija en el cielo y senala el Polo Norte geografico, por lo que ha sido empleado por navegantes como punto de referencia en sus travesias. Dada su ubicacion, la Osa Menor solo se puede ver en el hemisferio norte, pero a cambio, en dicho hemisferio se ve todo el ano. Junto con la Osa Mayor, es uno de los elementos mas caracteristicos del firmamento del hemisferio norte.";
	else if (A=="CEP")
		return "Cefeo es una constelacion del norte que representa al legendario rey de Etiopia Cefeo, esposo de Casiopea y padre de Andromeda. Es una de las 88 constelaciones modernas y una de las 48 constelaciones nombradas por Ptolomeo.";
	else if (A=="CHA")
		return "Chamaeleon (latin de Camaleon) es una constelacion menor del Sur. La constelacion fue una de las veinte constelaciones creadas por Pieter Dirkszoon Keyser y Frederick de Houtman entre los anos de 1595 y 1597, y su primera aparicion fue en el libro Uranometria de Johann Bayer de 1603.";
	else if (A=="CIR")
		return "Circinus o el Compas es una pequena y debil constelacion de los cielos meridionales delimitada por primera vez en 1756 por el astronomo frances Nicolas-Louis de Lacaille. Su estrella mas brillante es Alfa Circini que tiene una magnitud aparente de 3,19. Ligeramente variable, es la estrella Ap de oscilacion rapida mas brillante de los cielos nocturnos. AX Circini es una variable cefeida visible a simple vista y BX Circini es una estrella debil sospechosa de haberse formado a partir de la fusion de dos enanas blancas. Dos estrellas similares al Sol tienen sistemas planetarios: HD 134060 posee dos pequenos planetas y HD 129445 uno parecido a Jupiter. En el ano 185 observadores chinos registraron una supernova en esta constelacion, SN 185; ya en el siglo XX se registro la aparicion de dos novas.";
	else if (A=="COM")
		return "Coma Berenices o Cabellera de Berenice (esposa de Ptolomeo III). Constelacion situada cerca y al oeste de Leo.";
	else if (A=="CRA")
		return "Corona Australis o Corona Austrina (del latin Corona del Sur) es una de las 48 constelaciones nombradas por Ptolomeo en el siglo II, y una de las 88 constelaciones modernas.\nEs una constelacion pequena caracteristica de los cielos surenos que esta practicamente integrada a Sagitario, bordeandola al norte y oeste. En el este y sur tiene las constelaciones de Escorpio y Telescopium respectivamente. Debajo del arquero se ve un pequeno semicirculo de estrellas de magnitud 4 y 5, la Corona Austral.";
	else if (A=="CRB")
		return "Corona Boreal es una pequena constelacion boreal cuyas principales estrellas forman un arco semicircular. Esta es una de las 88 constelaciones modernas, y fue tambien una de las 48 constelaciones listadas por Ptolomeo, quien se refirio a la misma como Corona. La palabra Borealis fue anadida despues, en contraste con la Corona Australis, la Corona Austral.\nNo tiene estrellas de primera magnitud. Su estrella mas brillante, Alphecca, tambien conocida como Gemma, tiene una magnitud de 2,2 (ligeramente variable) y es considerada miembro difuso de la Asociacion estelar de la Osa Mayor. La constelacion contiene muchas estrellas variables interesantes: dos de las mas conocidas son R Coronae Borealis y T Coronae Borealis.";
	else if (A=="CRU")
		return "Crux (la Cruz), normalmente referida como la Cruz del Sur para contrastarla con la Cruz del Norte, es una de las mas famosas constelaciones modernas a pesar de ser la mas pequena de las 88 que integran la esfera celeste; segun los limites imaginarios impuestos por la Union Astronomica Internacional (UAI) en 1930. Esta constelacion esta compuesta por dos travesanos cruzados, uno de 4.2 y el otro de 5.4 grados de largo, y ocupa una zona de solo 68 grados cuadrados, por lo que cubre apenas 1/600 del cielo.\nEs util para la orientacion ya que permite determinar el punto cardinal sur: prolongando cuatro veces y media en linea recta el eje principal de la cruz, partiendo de su estrella mas brillante.";
	else if (A=="CRV")
		return "Corvus (el cuervo en latin) es una constelacion menor con solo 11 estrellas visibles a simple vista. Gienah Gurab y Algorab, sirven de indicadoras para encontrar a Espiga.";
	else if (A=="CVN")
		return "Canes Venatici (los perros cazadores o los lebreles), en castellano Lebreles, es una pequena constelacion del norte introducida por Johannes Hevelius en el siglo XVII.";
	else if (A=="CYG")
		return "Cygnus (el cisne) es una constelacion del hemisferio norte que atraviesa la Via Lactea. La disposicion de sus principales estrellas hace que a veces sea conocida como la Cruz del Norte, en contraste con la constelacion austral de la Cruz del Sur";
	else if (A=="DEL")
		return "Delphinus (el Delfin), es una pequena constelacion del hemisferio norte muy cerca del ecuador celestial. Fue incluida ya en la lista de Ptolomeo de 48 constelaciones y tambien forma la parte de la lista moderna de 88 constelaciones aprobadas por el IAU.\nDelphinus tiene el aspecto de un delfin al saltar y puede ser reconocida facilmente en el cielo. Se halla rodeada por Vulpecula (la zorra), Sagitta (la flecha), el aguila (Aquila), la constelacion zodiacal de Acuario, el pequeno caballo Equuleus y finalmente por Pegaso, el caballo alado. Otra forma de reconocerla es por tener una forma semejante a la de una cometa y por que es de pequeno tamano.";
	else if (A=="DRA")
		return "Draco (el Dragon) es una constelacion del norte lejano, que es circumpolar para muchos observadores del hemisferio norte. Es una de las 88 constelaciones modernas, y una de las 48 constelaciones listadas por Ptolomeo. El polo norte de la ecliptica es en Draco.\nAunque muy grande, Draco no tiene estrellas especialmente brillantes. La cabeza del dragon esta representada por un cuadrilatero de estrellas situadas entre Hercules y la Osa Menor.";
	else if (A=="EQU")
		return "Equuleus (el caballo) es la segunda mas pequena de las 88 constelaciones, solo superada por la Cruz del Sur. A pesar de ello y de no ser de las mas brillantes (ninguna de sus estrellas supera la magnitud 4), fue tambien una de las 48 constelaciones catalogadas por Ptolomeo.";
	else if (A=="GRU")
		return "Grus (la grulla), es una constelacion austral. Es una de las 20 constelaciones creadas por Pieter Dirkszoon Keyser y Frederick de Houtman entre los anos de 1595 y 1597, y su primera aparicion es en el libro Uranometria de Johann Bayer en 1603.";
	else if (A=="HER")
		return "Recibe su nombre del heroe mitologico, Hercules y es la quinta en tamano de las 88 constelaciones modernas. Tambien era una de las 48 constelaciones de Ptolomeo.";
	else if (A=="HYI")
		return "Hydrus (Latin para Hidra, tambien se refiera al \"Hidra macho\" o \"pequeno Hidra\") es una constelacion austral. Es una de las 20 constelaciones creadas por Pieter Dirkszoon Keyser y Frederick de Houtman entre los anos de 1595 y 1597, y su primera aparicion es en el libro Uranometria de Johann Bayer en 1603.\nNo debe confundirse con Hidra, la constelacion mas extensa del cielo nocturno.";
	else if (A=="IND")
		return "Indus (el Indio), es una constelacion austral que se supone representa un indigena americano.";
	else if (A=="LAC")
		return "Lacerta (genitivo Lacertae), el lagarto, es una de las 88 constelaciones reconocidas por la Union Astronomica Internacional. Esta situada a unos 20 grados al este de Deneb. El cuerpo del lagarto va en direccion norte-sur. Fue recogida en el atlas de Hevelius en 1690.";
	else if (A=="LIB")
		return "Libra (la balanza), es la septima constelacion del zodiaco en el cielo. Bastante discreta, no tiene estrellas de primera magnitud, estando situada entre Virgo al oeste y Escorpio al este, notablemente mas llamativas. Como se evidencia por los nombres de sus estrellas mas brillantes, fue en algun momento parte de las pinzas del escorpion: asi, Zubenelgenubi significa \"pinza del sur\" y Zubeneschamali \"pinza del norte\".";
	else if (A=="LUP")
		return "Lupus (el Lobo) es una constelacion del hemisferio sur ubicada entre las constelaciones de Centaurus y Scorpius. Se encuentra entre las patas del escorpion y casi unida a centauro. Desde Espana (incluyendo Europa central) solo se puede ver la parte mas septentrional de la constelacion, en el momento del transito por el meridiano, a comienzos del verano.";
	else if (A=="LYR")
		return "La constelacion de Lyra (la lira) no es grande pero es facilmente identificable por su estrella Vega, que es uno de los vertices del denominado \"Triangulo de verano\" (las otras dos estrellas son Deneb, en la constelacion del Cisne, y Altair, en el Aguila).";
	else if (A=="MEN")
		return "Mensa (latin para Mesa) es un constelacion austral, que fue introducida por Nicolas Louis de Lacaille bajo el nombre de Mons Mensae (Latin para meseta).\nEl nombre hace referencia especificamente a la Montana de la Mesa (equivalente literal a Mons Mensae en latin) en Sudafrica, desde donde Lacaille hizo importantes observaciones del cielo austral. La constelacion no contiene estrellas brillantes, asi Alfa Mensae su estrella mas brillante es apenas visible con una magnitud 5,08, haciendola la constelacion menos visible en el cielo, pero contiene parte de la Gran Nube de Magallanes (el resto se encuentra en la constelacion llamada Dorado).";
	else if (A=="MIC")
		return "Microscopium o el Microscopio es una pequena constelacion del hemisferio celeste meridional, una de las doce creadas en el siglo XVIII por el astronomo frances Nicolas-Louis de Lacaille. Representa un microscopio, un instrumento cientifico que permite observar objetos tan pequenos que no se pueden ver a simple vista. Sus estrellas son debiles y apenas visibles desde la mayor parte del hemisferio norte.";
	else if (A=="MUS")
		return "Musca (\"Mosca\" en latin) es una de las constelaciones menores del sur. La constelacion creada por Pieter Dirkszoon Keyser y Frederick de Houtman entre 1595 y 1597, y aparecio por primera vez en el libro Uranometria de Johann Bayer de 1603.";
	else if (A=="NOR")
		return "Norma o la Escuadra es una pequena constelacion del hemisferio celeste sur entre las constelaciones del Escorpion y Centauro, una de las doce recogidas en el siglo XVIII por el astronomo frances Nicolas-Louis de Lacaille y que representan a un instrumento cientifico. El nombre latino tambien aparece a veces traducido como la regla, la escuadra del carpintero o el nivel. Es una de las ochenta y ocho constelaciones modernas. Se da la circunstancia de que esta constelacion carece de estrellas alfa y beta.";
	else if (A=="OCT")
		return "Octans (Latin de octante) es una constelacion discreta presentada por Nicolas Louis de Lacaille. Es, fundamentalmente, conocida por ser la ubicacion del polo sur celeste.\nSu estrella Sigma Octantis es la estrella mas cercana del polo que puede ser vista por el ojo humano, pero es tan apagada, que es practicamente inutil como Estrella Polar para efectos de navegacion. Afortunadamente, la constelacion Crux, La Cruz del Sur, senala el polo.\nLa constelacion es circumpolar al Polo Sur Celeste, asi puede ser vista en los cielos del Hemisferio Sur durante las noches de cualquier mes del ano. La ascension recta y mes de mayor visibilidad dadas son para las tres estrellas mas brillantes, las cuales son las mas altas en el cielo durante las noches de noviembre.";
	else if (A=="OPH")
		return "Ofiuco u Ophiuchus (el portador de la serpiente o Serpentario) o tambien conocido como \"El cazador de serpientes\" es una de las 88 constelaciones modernas, y era una de las 48 listadas por Ptolomeo. Puede verse en ambos hemisferios entre los meses de abril a octubre por estar situada sobre el ecuador celeste.\nAl norte de Ofiuco se halla Hercules, al suroeste Sagitario (Sagittarius) y al sureste Escorpion (Scorpius); al este se encuentran la Cabeza de la Serpiente (Serpens Caput) y Libra, mientras que al oeste quedan Aguila (Aquila), Escudo de Sobieski (Scutum) y Cola de la Serpiente (Serpens Cauda). La constelacion queda flanqueada por la Cabeza y la Cola de la Serpiente, que puede ser considerada como una unica constelacion: Serpiente (Serpens), que la atraviesa. El conjunto resultante es un hombre rodeado por una serpiente.";
	else if (A=="PAV")
		return "Pavo es una constelacion del Hemisferio sur. La constelacion fue una de las veinte constelaciones creadas por Pieter Dirkszoon Keyser y Frederick de Houtman entre 1595 y 1597, y aparecio por primera vez en el libro Uranometria de Johann Bayer de 1603.";
	else if (A=="PSA")
		return "Piscis Austrinus o Piscis Australis (ambos del Latin para Pez del Sur) fue una de las 48 constelaciones listadas por Ptolomeo, y tambien es una de las 88 constelaciones modernas.";
	else if (A=="RET")
		return "Reticulum del (Latin: reticulo), es una de las menores constelaciones australes. Fue presentada por Nicolas Louis de Lacaille para conmemorar el reticulo, que fue un instrumento cientifico usado para medir la posicion de las estrellas.";
	else if (A=="SCO")
		return "Scorpius (el escorpion) tambien llamada Scorpio o Escorpio, es una de las 88 constelaciones. Antiguamente esta constelacion se representaba unida a la que hoy se conoce como Libra (que no existia, se cree que fueron los romanos quienes primero la imaginaron). Las estrellas que hoy se conocen como alfa y beta Librae representaban las pinzas sur y norte del escorpion, lo que les dio su nombre actual:\nAlfa librae: Zuben Elgenubi (garra del sur)\nBeta librae: Zuben Elschemali (garra del norte)\nRepresentado de esta forma, el escorpion colgaba apacible y equilibradamente sobre la ecliptica.";
	else if (A=="SCT")
		return "Scutum, el escudo, es una pequena constelacion del hemisferio sur celeste. Es una de las 88 constelaciones aceptadas por la Union Astronomica Internacional. Fue creada por Johannes Hevelius en 1690 bajo el nombre de Scutum Sobiescii o Scutum Sobiescianum (el \"escudo de Sobieski\"), para honrar al rey y heroe polaco Juan III Sobieski. Es la unica constelacion moderna que se asocia a una figura historica.\nLa sonda espacial Pioneer 11 fue lanzada el 6 de abril de 1973 en direccion a esta constelacion, pero como dejo de enviar senales a partir de noviembre de 1995, hoy esta viajando a la deriva.";
	else if (A=="SER")
		return "Serpens (la serpiente) es una de las 88 constelaciones modernas y era una de las 48 listadas por Ptolomeo. Entre las modernas constelaciones es la unica dividida en dos partes:\nSerpens Caput, que representa la cabeza de la serpiente, situada al oeste.\nSerpens Cauda, que representa la cola, al este.\nEntre estas dos partes se situa la constelacion de Ofiuco, el portador de la serpiente. Dado que se considera una unica constelacion, el ordenamiento de acuerdo a la denominacion de Bayer tiene en cuenta ambas partes.";
	else if (A=="SGE")
		return "Sagitta, (la Flecha), es una de las tres constelaciones mas pequenas, despues de Equuleus y Crux. Se encuentra dentro del perimetro del Triangulo Estival, el gran asterismo formado por Deneb, Vega y Altair.";
	else if (A=="SGR")
		return "Sagittarius (el arquero) es una constelacion del zodiaco, generalmente representada como un centauro sosteniendo un arco. Sagittarius se encuentra entre Scorpius al oeste y Capricornus al este.";
	else if (A=="APS")
		return "Apus (el ave del paraiso) es una constelacion del sur. Aparece por primera vez en Uranometria de Johann Bayer (ano 1603), pero pudo haber sido usada por navegantes con anterioridad.";
	else if (A=="AQL")
		return "Aquila (el Aguila) es una de las 48 constelaciones listadas por Ptolomeo, mencionada tambien por Eudoxo de Cnidos (siglo IV a. C.) y Arato (siglo III a. C.), y actualmente una de las 88 constelaciones reconocidas por la IAU. Ptolomeo catalogo diecinueve estrellas conjuntamente en esta constelacion y en la constelacion de Antinoo, esta ultima surgida durante el reinado de Adriano (117-138 d. C.). Ocupaba la parte sur de la constelacion actual de Aquila hasta principios del siglo XIX, cuando fue descartada.";
	else if (A=="AQR")
		return "Acuario (el portador del Agua o anfora), es una de las 88 constelaciones reconocidas por la astronomia moderna, descrita por Claudio Ptolomeo. Su simbolo representa el flujo del agua.\nDe todo el zodiaco, Acuario es una de las constelaciones reconocida con mayor antigüedad. Los sumerios le dieron este nombre a la constelacion, en honor a su dios An, que derrama el agua de la inmortalidad sobre la Tierra. Se encuentra en una region comunmente llamada el Mar o Aqua por su prodifusion de constelaciones acuaticas tales como Cetus, Piscis, Eridanus. Algunas veces el rio Eridanus se representa como lo que derrama la vasija de Acuario.";
	else if (A=="ARA")
		return "Ara, el altar, es una constelacion austral situada entre Scorpius y Triangulum Australe. Es una de las 48 constelaciones recogidas por Ptolomeo en el siglo II y una de las 88 constelaciones actuales.";
	else if (A=="VOL")
		return "Volans, el pez volador, es una constelacion que solo se puede ver, practicamente, desde lugares localizados en el hemisferio sur terrestre (a excepcion de algunos lugares en el hemisferio norte, proximos al ecuador). Esta fue una de las creaciones de los navegantes holandeses Pieter Dirkszoon Keyser y Frederick de Houtman entre los anos 1595 y 1597. Aparecio por primera vez en los mapas estelares preparados por el astronomo aleman Johann Bayer publicados en Uranometria (1603).";
	else if (A=="VUL")
		return "Vulpecula, La zorra o La Raposilla, es una pequena constelacion del norte ubicada en medio del Triangulo de verano, al norte de Sagitta y Delphinus. No contiene ninguna estrella brillante.";
	else if (A=="BOO")
		return "Bootes o el Boyero es una de las 88 constelaciones modernas y era una de las 48 constelaciones listadas por Ptolomeo. Bootes parece ser una figura humana grande, mirando hacia la Osa Mayor";
	else if (A=="CAP")
		return "Capricornus (la cabra mitad pez) es una de las constelaciones del Zodiaco, llamada comunmente Capricornio, sobre todo en lo referente a la astrologia. Aunque a veces se representa como una cabra, generalmente se le anade una cola de pez.";
	else if (A=="TUC")
		return "Tucana, el tucan, es una constelacion del hemisferio sur celeste. Es una de las 88 constelaciones aceptadas por la Union Astronomica Internacional. Fue creada por los navegantes holandeses Pieter Dirkszoon Keyser y Frederick de Houtman entre 1595 y 1597, como resultado de sus exploraciones por los mares del hemisferio sur. Aparecio por primera vez en la obra Uranometria (1603), de Johann Bayer. Representa al tucan, una especie de ave tropical oriunda de Suramerica.";
	else if (A=="TRA")
		return "Triangulum Australe es una pequena constelacion austral cuyas tres estrellas mas brillantes, de segunda y tercera magnitud, forman casi un triangulo equilatero. Esta constelacion fue introducida por Johann Bayer en 1603.\nNo debe ser confundida con la constelacion boreal de Triangulum.";
	else if (A=="TEL")
		return "Telescopium o el Telescopio es una pequena constelacion del hemisferio celeste austral, una de las doce conformadas en el siglo XVIII por el astronomo frances Nicolas-Louis de Lacaille y nombradas con instrumentos cientificos.\nLa estrella mas brillante de la constelacion es Alfa Telescopii, una subgigante blancoazulada con una magnitud aparente de 3,5; le sigue Zeta Telescopii, una gigante naranja con 4,1 de magnitud. Eta y PZ Telescopii son dos sistemas estelares jovenes rodeados de discos de escombros que tienen sendas enanas marrones de companeras.";
	else
		return "Error, check for: "+A;

}