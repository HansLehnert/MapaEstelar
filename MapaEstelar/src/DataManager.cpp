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
		return "Orion, (el Cazador), es una constelacion prominente, quizas la mas conocida del cielo. Sus estrellas brillantes y visibles desde ambos hemisferios hacen que esta constelacion sea reconocida mundialmente. La constelacion es visible a lo largo de toda la noche durante el invierno en el hemisferio norte, verano en hemisferio sur; es asimismo visible pocas horas antes del amanecer desde finales del mes de agosto hasta mediados de noviembre y puede verse en el cielo nocturno hasta mediados de abril. Orión se encuentra cerca de la constelación del río Eridanus y apoyado por sus dos perros de caza Canis Maior y Canis Minor peleando con la constelación del Tauro.";
	else if (A=="GEM")
		return "Gemini (los mellizos) es la tercera constelación del zodíaco, y se encuentra a unos treinta grados al noroeste de Orión. William Herschel descubrió Urano cerca de eta Geminorum en 1781, y Clyde Tombaugh hizo lo propio con Plutón cerca de delta Geminorum.";
	else if (A=="CNC")
		return "Cáncer (el cangrejo), en astronomía, es una de las doce constelaciones del zodíaco. En astrología, Cáncer constituye uno de los doce signos zodiacales. La constelación de Cáncer es pequeña y débil. Se encuentra entre las constelaciones de Géminis al este, Lince al norte y las constelaciones de Canis Minor e Hidra al sur.\nLa constelación también da su nombre al trópico de Cáncer.";
	else if (A=="CMI")
		return "Canis Minor, en castellano Can Menor (el perro pequeño) es una de las 88 constelaciones modernas. Formó parte también de forma evidente de las 48 constelaciones primitivas del Almagesto de Ptlolomeo, dato que se encuentra incluido en la fuente de este último trabajo: la gran obra denominada Astronómica de Manilio de Antioquía. La figura del Can menor es simple: una línea que une dos estrellas. Procyon su estrella más brillante forma junto con Betelgeuse (Orión) y Sirio (Can Mayor) el \"Triángulo de Invierno\".";
	else if (A=="CMA")
		return "El Can Mayor (Canis Maior) es una constelación que parece seguir, en su recorrido en el cielo debido al movimiento diurno, al \"Gran Cazador\", Orión.";
	else if (A=="MON")
		return "Monoceros (en griego unicornio) es una constelación en el cielo nocturno invernal del hemisferio norte, rodeada por Orión al oeste, Géminis al norte, el Can Mayor al sur e Hydra hacia el este. Otras constelaciones limítrofes son el Can Menor, Lepus y Puppis.";
	else if (A=="LEP")
		return "Lepus (la liebre en latín), es una constelación situada justo al sur de Orión, y posiblemente representa una liebre siendo perseguida por él. Lepus fue una de las 48 constelaciones de Ptolomeo y hoy es una de las 88 constelaciones modernas.\nEsta constelación no debe ser confundida con Lupus, el lobo.";
	else if (A=="SEX")
		return "Sextans (el Sextante) es una constelación menor del sur que fue introducida en el siglo XVII por Johannes Hevelius. La introdujo en recuerdo al instrumento que perdió en un incendio. Está situada entre Leo e Hydra y no es una constelación particularmente brillante. No hay mitología asociada a esta constelación.";
	else if (A=="PYX")
		return "Pyxis o la Brújula es una constelación pequeña y débil del hemisferio celeste meridional. Fue introducida en el siglo XVIII por Nicolas-Louis de Lacaille con el nombre de Pyxis Nautica y se cuenta entre las ochenta y ocho constelaciones modernas. Está situada cerca de la antigua constelación de Argo Navis; en el siglo XIX John Herschel sugirió renombrarla Malus, el Mástil, pero la sugerencia no prosperó. La Brújula es completamente visible en latitudes más al sur de los 53 grados norte, siendo febrero y marzo los meses de mejor visibilidad.\nEsta constelación está atravesada por la Vía Láctea.";
	else if (A=="TRI")
		return "Triangulum (el \"Triángulo\") es una pequeña constelación del norte, cuyas tres estrellas más brillantes, de tercera y cuarta magnitud, forman un triángulo casi isósceles. Es una de las 88 constelaciones modernas y también fue una de las 48 listadas por Ptolomeo. No debe ser confundida con la constelación austral Triangulum Australe.";
	else if (A=="ARI")
		return "Aries (el carnero) es una de las constelaciones del zodíaco; se encuentra entre las constelaciones de Piscis, al oeste, y Tauro al este.";
	else if (A=="LEO")
		return "Leo (el león) es una de las constelaciones del zodíaco. Se encuentra entre Cáncer y Virgo.";
	else if (A=="LMI")
		return "Leo Minor (latín de León Menor) es de las constelaciones más pequeñas: apenas puede ser reconocida como un triángulo y está situada entre las fácilmente reconocibles Osa Mayor y Leo. A diferencia de Leo no pertenece a la antigua lista de 48 constelaciones dibujadas por Ptolomeo en el segundo siglo a. C., sino que fue creada por Johannes Hevelius en 1687.";
	else if (A=="LYN")
		return "Lince (en inglés Lynx) es una constelación del Hemisferio norte, introducido en el siglo XVII por Johannes Hevelius. El origen del nombre se debe a la poca luminosidad de sus astros, pues se necesita tener ojos de lince para poder verla. Para localizar al Lince hay que buscar entre dos constelaciones muy luminosas, la Osa Mayor y Auriga.";
	else if (A=="VIR")
		return "Virgo (la virgen) es una constelación del zodíaco. Se encuentra entre Leo al oeste y Libra al este y es una de las constelaciones más grandes visibles en el cielo.";
	else if (A=="VEL")
		return "Vela es una constelación austral, una de las cuatro partes en que fue dividida la constelación de Argo Navis (el navío Argos), siendo las otras Carina (la quilla), Puppis (la popa) y Pyxis (la brújula).";
	else if (A=="CEN")
		return "Centaurus (el centauro), es una extensa constelación que se encuentra al norte de Crux y en el extremo norte de la Vía Láctea. Rodea la Cruz del Sur formando una de las más ricas y hermosas constelaciones del cielo.";
	else if (A=="CRT")
		return "Crater (taza en Latín) es una de las 88 constelaciones y también fue una de las 48 listadas por Ptolomeo. Se dice que representa la copa de Apolo. No tiene estrella con brillo mayor a la cuarta magnitud.";
	else if (A=="ANT")
		return "Antlia o la Bomba Neumática es una constelación del hemisferio celeste austral. Su nombre hace referencia al aparato inventado por el físico francés Denis Papin en el siglo XVII. La constelación fue introducida por Nicolas-Louis de Lacaille, con el nombre de Antlia Pneumatica, cuando estuvo trabajando en el observatorio del cabo de Buena Esperanza y se cuenta entre las ochenta y ocho constelaciones modernas. Situada cerca de las estrellas que formaban la antigua constelación de Argo Navis, Antlia es completamente visible desde latitudes más al sur de los 49 grados norte.";
	else if (A=="HYA")
		return "Hidra es la más grande de las 88 constelaciones modernas, y fue una de las 48 constelaciones que Ptolomeo registró. No debe ser confundida con Hydrus, constelación del hemisferio sur de menor tamaño.";
	else if (A=="PUP")
		return "Puppis (\"Popa\" en latín) es una constelación austral. Es la mayor de las tres partes en las que se separó la constelación Nave Argo.";
	else if (A=="COL")
		return "Columba, Latín para paloma, es una pequeña constelación justo al sur de Canis Major y Lepus. Fue sacada de la constelación Canis Major por Augustin Royer, en 1679.";
	else if (A=="CAR")
		return "Carina (la quilla), en castellano Quilla, es una constelación austral que forma parte de la antigua constelación de Argo Navis (el navío Argo). La Unión Astronómica Internacional la dividió en cuatro componentes: Carina (la Quilla), Vela (la Vela), Puppis (la Popa) y Pyxis (el compás o la brújula).";
	else if (A=="CAS")
		return "Casiopea es una de las constelaciones compiladas en el catálogo estelar de Tolomeo, el Almagesto, del siglo II. Fácilmente reconocible por sus cinco estrellas brillantes que forman un conocido asterismo del cielo circumpolar boreal.\nCasiopea señala al norte (y a la estrella Polar) apuntando desde sus extremos de la M o W. Tiene al otro lado al Gran Carro de la Osa Mayor.\nAl ser tan fácil de reconocer es muy usada para encontrar el norte cuando no es posible utilizar a la Osa Mayor para este propósito, cuando ésta no es visible en cielos de latitudes templadas (menos de 35 grados N - Islas Canarias).";
	else if (A=="PIC")
		return "Pictor o el Caballete del Pintor es una constelación de los cielos australes que se encuentra entre la estrella Canopus y la Gran Nube de Magallanes. Fue creada por el astrónomo francés del siglo XVIII Nicolas-Louis de Lacaille con el nombre de Equuleus Pictoris; normalmente se representa con un caballete. La estrella más brillante de la constelación es Alfa Pictoris, una estrella blanca de la secuencia principal a unos 97 años luz de la Tierra. Pictor también alberga a RR Pictoris, un sistema de estrellas variables cataclísmicas que estalló como nova en 1925, alcanzando una magnitud aparente de 1,2 para desaparecer después en la oscuridad.";
	else if (A=="DOR")
		return "Dorado es una constelación austral, creada por Pieter Dirkszoon Keyser y Frederick de Houtman entre 1595 y 1597, y listada por primera vez en la Uranometria de Johann Bayer de 1603; conocida también como \"Pez Espada\", recibe su nombre en realidad del dorado delfín o mahi-mahi, Coryphaena hippurus, un pez comestible nativo de América. En ella es visible la mayor parte de la Gran Nube de Magallanes.";
	else if (A=="AND")
		return "Andrómeda es una constelación boreal situada al sur de Casiopea y cerca de Pegaso. Toma su nombre de la doncella Andrómeda de la mitología griega. Comparte una estrella con Pegaso, la estrella blanco-azulada de la esquina noroeste del Cuadrante de Pegaso, denominada Alpheratz o Sirrah.";
	else if (A=="TAU")
		return "Tauro o Taurus es una constelación zodiacal; su nombre en latín es Taurus y en español toro. Destaca en el cielo invernal, entre Aries al oeste y Géminis al este. Al norte se encuentran Perseo y Auriga; al sureste Orión, y al suroeste Eridanus y Cetus.\nEn el zodíaco es el segundo signo. Como tal, en la antigüedad contenía la constelación del mismo nombre, pero la precesión de los equinoccios ha hecho que el signo de Tauro se encuentre ocupado por la constelación de Aries. Actualmente el sol brilla sobre Tauro entre el 14 de mayo y el 21 de junio.";
	else if (A=="AUR")
		return "Auriga (el cochero), en castellano Cochero, es una constelación del hemisferio norte. Su localización es fácil: basta con mirar por encima de Orión. Se ve un pentágono de estrellas brillantes, entre las que destaca Capella.";
	else if (A=="HOR")
		return "Horologium (el Reloj) es uno de las menores constelaciones del sur (declinación cerca de -60 grados).\nOriginalmente llamado Horologium Oscillitorium por Nicolas Louis de Lacaille, el nombre de la constelación ha sido acortado para que sea menos pesado. Horologium Oscillitorium se puso en honor al inventor del reloj de péndulo, Christian Huygens.";
	else if (A=="CAE")
		return "Caelum o el Cincel es una débil constelación del hemisferio celeste austral introducida por Nicolas-Louis de Lacaille en la década de los 50 del siglo XVIII con el nombre de Caelum Scalptorium. Se cuenta entre las ochenta y ocho constelaciones modernas. Es la octava constelación más pequeña y subyace bajo un ángulo de alrededor de 0,038 estereorradianes, algo menor que el de Corona Australis.\nDebido a su pequeño tamaño y su ubicación lejos del plano de la Vía Láctea, Caelum es una constelación bastante desolada que contiene pocos objetos de interés.";
	else if (A=="SCL")
		return "Sculptor es una constelación menor del sur, que fue presentada por Nicolas Louis de Lacaille. Originalmente la llamó 'Estudio de escultor', pero posteriormente, el nombre fue acortado.\nSculptor contiene el polo galáctico del sur.";
	else if (A=="CET")
		return "Cetus (la ballena o el monstruo marino) es una constelación del hemisferio sur, en una región conocida como Agua, cerca de otras constelaciones como Aquarius, Piscis y Eridanus.";
	else if (A=="FOR")
		return "Fornax (el horno) es una constelación austral que fue introducida por Nicolas Louis de Lacaille bajo el nombre de Fornax Chemica (latín para horno químico).";
	else if (A=="PHE")
		return "Fénix, (el Fénix) es una constelación menor del sur, introducida por los navegantes daneses Pieter Dirkszoon Keyser y Frederick de Houtman, y popularizada por el libro Uranometria de Johann Bayer en 1603.\nSólo hay treinta estrellas en toda la constelación, las cuales tienen un brillo de una magnitud mayor a 5.0.\nLa extensión aproximada de la constelación es -41 grados hasta -57 grados declinación, y desde 23,5h hasta 2h de ascensión recta. Esto significa que es generalmente invisible para cualquiera que viva al norte del paralelo 40 en el Hemisferio Norte, y permanece bajo en el cielo para el que viva al norte del Ecuador. Es fácilmente visible desde lugares como Australia, Sudamérica y Sudáfrica durante el verano del Hemisferio Sur.\nFénix es asociado con la llúvia de estrellas Fenícidas que ocurre cada 5 de diciembre.";
	else if (A=="CAM")
		return "Camelopardalis, la jirafa, es una gran constelación del hemisferio norte celeste muy poco conspicua, pues sus estrellas más brillantes (siete) son sólo de magnitud 5. Está situada entre las constelaciones de Auriga y las dos Osas. El nombre de Camelopardalis proviene de \"camello-leopardo\", nombre que los griegos dieron a la jirafa, ya que pensaban que tenía la cabeza de camello y las manchas de leopardo.\nFue introducida como constelación por Petrus Plancius y publicada por Jakob Bartsch en 1624 en su libro sobre las constelaciones.";
	else if (A=="ERI")
		return "Eridanus es la sexta constelación más grande de las 88 constelaciones modernas. También es una de las 48 constelaciones de Ptolomeo.";
	else if (A=="PEG")
		return "Pegaso (el caballo alado) es una constelación del norte, que recibe su nombre del Pegaso mítico. Es una de las 88 constelaciones modernas y una de las 48 inicialmente descritas por Ptolomeo.";
	else if (A=="PER")
		return "Perseo es una constelación del norte y representa a Perseo, héroe mitológico que decapitó a Medusa. Es una de las 48 constelaciones de Ptolomeo así como una de las 88 constelaciones modernas. En ella está la famosa variable Algol, y en ella se localiza la lluvia de meteoros de las perseidas.";
	else if (A=="PSC")
		return "Pisces (los peces) es una constelación del zodiaco ubicada entre Aquarius al oeste y Aries hacia el este.";
	else if (A=="UMA")
		return "La Osa Mayor (en latín, Ursa Major; abreviado, UMa), también conocida como el Carro Mayor, es una constelación visible durante todo el año en el hemisferio norte. Entre los aficionados se le conoce con el nombre de \"el carro\", por la forma que dibujan sus siete estrellas principales, aunque ha recibido otros muchos nombres.";
	else if (A=="UMI")
		return "La Osa Menor, ursa en latín, es una constelación del hemisferio norte. Comparte el mismo nombre que la Osa Mayor, debido a que su cola se asemeja al mango de una cuchara: consta de siete estrellas con la forma de carro; cuatro de ellas forman lo que es la parte honda del carro y las otras tres son el mango del carro. Fue una de las 48 constelaciones enumeradas originalmente por el astrónomo Claudio Ptolomeo en el siglo II, y desde entonces forma parte de las 88 constelaciones contemporáneas.\nEl elemento más conocido de la Osa Menor es la estrella Polar, la cual se encuentra situada aproximadamente en la prolongación del eje de la Tierra, de modo que permanece casi fija en el cielo y señala el Polo Norte geográfico, por lo que ha sido empleado por navegantes como punto de referencia en sus travesías. Dada su ubicación, la Osa Menor sólo se puede ver en el hemisferio norte, pero a cambio, en dicho hemisferio se ve todo el año. Junto con la Osa Mayor, es uno de los elementos más característicos del firmamento del hemisferio norte.";
	else if (A=="CEP")
		return "Cefeo es una constelación del norte que representa al legendario rey de Etiopía Cefeo, esposo de Casiopea y padre de Andrómeda. Es una de las 88 constelaciones modernas y una de las 48 constelaciones nombradas por Ptolomeo.";
	else if (A=="CHA")
		return "Chamaeleon (latín de Camaleón) es una constelación menor del Sur. La constelación fue una de las veinte constelaciones creadas por Pieter Dirkszoon Keyser y Frederick de Houtman entre los años de 1595 y 1597, y su primera aparición fue en el libro Uranometria de Johann Bayer de 1603.";
	else if (A=="CIR")
		return "Circinus o el Compás es una pequeña y débil constelación de los cielos meridionales delimitada por primera vez en 1756 por el astrónomo francés Nicolas-Louis de Lacaille. Su estrella más brillante es Alfa Circini que tiene una magnitud aparente de 3,19. Ligeramente variable, es la estrella Ap de oscilación rápida más brillante de los cielos nocturnos. AX Circini es una variable cefeida visible a simple vista y BX Circini es una estrella débil sospechosa de haberse formado a partir de la fusión de dos enanas blancas. Dos estrellas similares al Sol tienen sistemas planetarios: HD 134060 posee dos pequeños planetas y HD 129445 uno parecido a Júpiter. En el año 185 observadores chinos registraron una supernova en esta constelación, SN 185; ya en el siglo XX se registró la aparición de dos novas.";
	else if (A=="COM")
		return "Coma Berenices o Cabellera de Berenice (esposa de Ptolomeo III). Constelación situada cerca y al oeste de Leo.";
	else if (A=="CRA")
		return "Corona Australis o Corona Austrina (del latín Corona del Sur) es una de las 48 constelaciones nombradas por Ptolomeo en el siglo II, y una de las 88 constelaciones modernas.\nEs una constelación pequeña característica de los cielos sureños que está prácticamente integrada a Sagitario, bordeándola al norte y oeste. En el este y sur tiene las constelaciones de Escorpio y Telescopium respectivamente. Debajo del arquero se ve un pequeño semicírculo de estrellas de magnitud 4 y 5, la Corona Austral.";
	else if (A=="CRB")
		return "Corona Boreal es una pequeña constelación boreal cuyas principales estrellas forman un arco semicircular. Esta es una de las 88 constelaciones modernas, y fue también una de las 48 constelaciones listadas por Ptolomeo, quien se refirió a la misma como Corona. La palabra Borealis fue añadida después, en contraste con la Corona Australis, la Corona Austral.\nNo tiene estrellas de primera magnitud. Su estrella más brillante, Alphecca, también conocida como Gemma, tiene una magnitud de 2,2 (ligeramente variable) y es considerada miembro difuso de la Asociación estelar de la Osa Mayor. La constelación contiene muchas estrellas variables interesantes: dos de las más conocidas son R Coronae Borealis y T Coronae Borealis.";
	else if (A=="CRU")
		return "Crux (la Cruz), normalmente referida como la Cruz del Sur para contrastarla con la Cruz del Norte, es una de las más famosas constelaciones modernas a pesar de ser la más pequeña de las 88 que integran la esfera celeste; según los límites imaginarios impuestos por la Unión Astronómica Internacional (UAI) en 1930. Esta constelación está compuesta por dos travesaños cruzados, uno de 4.2 y el otro de 5.4 grados de largo, y ocupa una zona de solo 68 grados cuadrados, por lo que cubre apenas 1/600 del cielo.\nEs útil para la orientación ya que permite determinar el punto cardinal sur: prolongando cuatro veces y media en línea recta el eje principal de la cruz, partiendo de su estrella más brillante.";
	else if (A=="CRV")
		return "Corvus (el cuervo en latín) es una constelación menor con sólo 11 estrellas visibles a simple vista. Gienah Gurab y Algorab, sirven de indicadoras para encontrar a Espiga.";
	else if (A=="CVN")
		return "Canes Venatici (los perros cazadores o los lebreles), en castellano Lebreles, es una pequeña constelación del norte introducida por Johannes Hevelius en el siglo XVII.";
	else if (A=="CYG")
		return "Cygnus (el cisne) es una constelación del hemisferio norte que atraviesa la Vía Láctea. La disposición de sus principales estrellas hace que a veces sea conocida como la Cruz del Norte, en contraste con la constelación austral de la Cruz del Sur";
	else if (A=="DEL")
		return "Delphinus (el Delfín), es una pequeña constelación del hemisferio norte muy cerca del ecuador celestial. Fue incluida ya en la lista de Ptolomeo de 48 constelaciones y también forma la parte de la lista moderna de 88 constelaciones aprobadas por el IAU.\nDelphinus tiene el aspecto de un delfín al saltar y puede ser reconocida fácilmente en el cielo. Se halla rodeada por Vulpecula (la zorra), Sagitta (la flecha), el águila (Aquila), la constelación zodiacal de Acuario, el pequeño caballo Equuleus y finalmente por Pegaso, el caballo alado. Otra forma de reconocerla es por tener una forma semejante a la de una cometa y por que es de pequeño tamaño.";
	else if (A=="DRA")
		return "Draco (el Dragón) es una constelación del norte lejano, que es circumpolar para muchos observadores del hemisferio norte. Es una de las 88 constelaciones modernas, y una de las 48 constelaciones listadas por Ptolomeo. El polo norte de la eclíptica es en Draco.\nAunque muy grande, Draco no tiene estrellas especialmente brillantes. La cabeza del dragón está representada por un cuadrilátero de estrellas situadas entre Hércules y la Osa Menor.";
	else if (A=="EQU")
		return "Equuleus (el caballo) es la segunda más pequeña de las 88 constelaciones, sólo superada por la Cruz del Sur. A pesar de ello y de no ser de las más brillantes (ninguna de sus estrellas supera la magnitud 4), fue también una de las 48 constelaciones catalogadas por Ptolomeo.";
	else if (A=="GRU")
		return "Grus (la grulla), es una constelación austral. Es una de las 20 constelaciones creadas por Pieter Dirkszoon Keyser y Frederick de Houtman entre los años de 1595 y 1597, y su primera aparición es en el libro Uranometria de Johann Bayer en 1603.";
	else if (A=="HER")
		return "Recibe su nombre del héroe mitológico, Hércules y es la quinta en tamaño de las 88 constelaciones modernas. También era una de las 48 constelaciones de Ptolomeo.";
	else if (A=="HYI")
		return "Hydrus (Latín para Hidra, también se refiera al \"Hidra macho\" o \"pequeño Hidra\") es una constelación austral. Es una de las 20 constelaciones creadas por Pieter Dirkszoon Keyser y Frederick de Houtman entre los años de 1595 y 1597, y su primera aparición es en el libro Uranometria de Johann Bayer en 1603.\nNo debe confundirse con Hidra, la constelación más extensa del cielo nocturno.";
	else if (A=="IND")
		return "Indus (el Indio), es una constelación austral que se supone representa un indígena americano.";
	else if (A=="LAC")
		return "Lacerta (genitivo Lacertae), el lagarto, es una de las 88 constelaciones reconocidas por la Unión Astronómica Internacional. Está situada a unos 20 grados al este de Deneb. El cuerpo del lagarto va en dirección norte-sur. Fue recogida en el atlas de Hevelius en 1690.";
	else if (A=="LIB")
		return "Libra (la balanza), es la séptima constelación del zodiaco en el cielo. Bastante discreta, no tiene estrellas de primera magnitud, estando situada entre Virgo al oeste y Escorpio al este, notablemente más llamativas. Como se evidencia por los nombres de sus estrellas más brillantes, fue en algún momento parte de las pinzas del escorpión: así, Zubenelgenubi significa \"pinza del sur\" y Zubeneschamali \"pinza del norte\".";
	else if (A=="LUP")
		return "Lupus (el Lobo) es una constelación del hemisferio sur ubicada entre las constelaciones de Centaurus y Scorpius. Se encuentra entre las patas del escorpión y casi unida a centauro. Desde España (incluyendo Europa central) sólo se puede ver la parte más septentrional de la constelación, en el momento del tránsito por el meridiano, a comienzos del verano.";
	else if (A=="LYR")
		return "La constelación de Lyra (la lira) no es grande pero es fácilmente identificable por su estrella Vega, que es uno de los vértices del denominado \"Triángulo de verano\" (las otras dos estrellas son Deneb, en la constelación del Cisne, y Altair, en el Águila).";
	else if (A=="MEN")
		return "Mensa (latín para Mesa) es un constelación austral, que fue introducida por Nicolas Louis de Lacaille bajo el nombre de Mons Mensae (Latín para meseta).\nEl nombre hace referencia específicamente a la Montaña de la Mesa (equivalente literal a Mons Mensae en latín) en Sudáfrica, desde donde Lacaille hizo importantes observaciones del cielo austral. La constelación no contiene estrellas brillantes, así Alfa Mensae su estrella más brillante es apenas visible con una magnitud 5,08, haciéndola la constelación menos visible en el cielo, pero contiene parte de la Gran Nube de Magallanes (el resto se encuentra en la constelación llamada Dorado).";
	else if (A=="MIC")
		return "Microscopium o el Microscopio es una pequeña constelación del hemisferio celeste meridional, una de las doce creadas en el siglo XVIII por el astrónomo francés Nicolas-Louis de Lacaille. Representa un microscopio, un instrumento científico que permite observar objetos tan pequeños que no se pueden ver a simple vista. Sus estrellas son débiles y apenas visibles desde la mayor parte del hemisferio norte.";
	else if (A=="MUS")
		return "Musca (\"Mosca\" en latín) es una de las constelaciones menores del sur. La constelación creada por Pieter Dirkszoon Keyser y Frederick de Houtman entre 1595 y 1597, y apareció por primera vez en el libro Uranometria de Johann Bayer de 1603.";
	else if (A=="NOR")
		return "Norma o la Escuadra es una pequeña constelación del hemisferio celeste sur entre las constelaciones del Escorpión y Centauro, una de las doce recogidas en el siglo XVIII por el astrónomo francés Nicolas-Louis de Lacaille y que representan a un instrumento científico. El nombre latino también aparece a veces traducido como la regla, la escuadra del carpintero o el nivel. Es una de las ochenta y ocho constelaciones modernas. Se da la circunstancia de que esta constelación carece de estrellas alfa y beta.";
	else if (A=="OCT")
		return "Octans (Latín de octante) es una constelación discreta presentada por Nicolas Louis de Lacaille. Es, fundamentalmente, conocida por ser la ubicación del polo sur celeste.\nSu estrella Sigma Octantis es la estrella más cercana del polo que puede ser vista por el ojo humano, pero es tan apagada, que es prácticamente inútil como Estrella Polar para efectos de navegación. Afortunadamente, la constelación Crux, La Cruz del Sur, señala el polo.\nLa constelación es circumpolar al Polo Sur Celeste, así puede ser vista en los cielos del Hemisferio Sur durante las noches de cualquier mes del año. La ascensión recta y mes de mayor visibilidad dadas son para las tres estrellas más brillantes, las cuales son las más altas en el cielo durante las noches de noviembre.";
	else if (A=="OPH")
		return "Ofiuco u Ophiuchus (el portador de la serpiente o Serpentario) o también conocido como \"El cazador de serpientes\" es una de las 88 constelaciones modernas, y era una de las 48 listadas por Ptolomeo. Puede verse en ambos hemisferios entre los meses de abril a octubre por estar situada sobre el ecuador celeste.\nAl norte de Ofiuco se halla Hércules, al suroeste Sagitario (Sagittarius) y al sureste Escorpión (Scorpius); al este se encuentran la Cabeza de la Serpiente (Serpens Caput) y Libra, mientras que al oeste quedan Águila (Aquila), Escudo de Sobieski (Scutum) y Cola de la Serpiente (Serpens Cauda). La constelación queda flanqueada por la Cabeza y la Cola de la Serpiente, que puede ser considerada como una única constelación: Serpiente (Serpens), que la atraviesa. El conjunto resultante es un hombre rodeado por una serpiente.";
	else if (A=="PAV")
		return "Pavo es una constelación del Hemisferio sur. La constelación fue una de las veinte constelaciones creadas por Pieter Dirkszoon Keyser y Frederick de Houtman entre 1595 y 1597, y apareció por primera vez en el libro Uranometria de Johann Bayer de 1603.";
	else if (A=="PSA")
		return "Piscis Austrinus o Piscis Australis (ambos del Latín para Pez del Sur) fue una de las 48 constelaciones listadas por Ptolomeo, y también es una de las 88 constelaciones modernas.";
	else if (A=="RET")
		return "Reticulum del (Latín: retículo), es una de las menores constelaciones australes. Fue presentada por Nicolas Louis de Lacaille para conmemorar el retículo, que fue un instrumento científico usado para medir la posición de las estrellas.";
	else if (A=="SCO")
		return "Scorpius (el escorpión) también llamada Scorpio o Escorpio, es una de las 88 constelaciones. Antiguamente esta constelación se representaba unida a la que hoy se conoce como Libra (que no existía, se cree que fueron los romanos quienes primero la imaginaron). Las estrellas que hoy se conocen como alfa y beta Librae representaban las pinzas sur y norte del escorpión, lo que les dio su nombre actual:\nAlfa librae: Zuben Elgenubi (garra del sur)\nBeta librae: Zuben Elschemali (garra del norte)\nRepresentado de esta forma, el escorpión colgaba apacible y equilibradamente sobre la eclíptica.";
	else if (A=="SCT")
		return "Scutum, el escudo, es una pequeña constelación del hemisferio sur celeste. Es una de las 88 constelaciones aceptadas por la Unión Astronómica Internacional. Fue creada por Johannes Hevelius en 1690 bajo el nombre de Scutum Sobiescii o Scutum Sobiescianum (el \"escudo de Sobieski\"), para honrar al rey y héroe polaco Juan III Sobieski. Es la única constelación moderna que se asocia a una figura histórica.\nLa sonda espacial Pioneer 11 fue lanzada el 6 de abril de 1973 en dirección a esta constelación, pero como dejó de enviar señales a partir de noviembre de 1995, hoy está viajando a la deriva.";
	else if (A=="SER")
		return "Serpens (la serpiente) es una de las 88 constelaciones modernas y era una de las 48 listadas por Ptolomeo. Entre las modernas constelaciones es la única dividida en dos partes:\nSerpens Caput, que representa la cabeza de la serpiente, situada al oeste.\nSerpens Cauda, que representa la cola, al este.\nEntre estas dos partes se sitúa la constelación de Ofiuco, el portador de la serpiente. Dado que se considera una única constelación, el ordenamiento de acuerdo a la denominación de Bayer tiene en cuenta ambas partes.";
	else if (A=="SGE")
		return "Sagitta, (la Flecha), es una de las tres constelaciones más pequeñas, después de Equuleus y Crux. Se encuentra dentro del perímetro del Triángulo Estival, el gran asterismo formado por Deneb, Vega y Altair.";
	else if (A=="SGR")
		return "Sagittarius (el arquero) es una constelación del zodíaco, generalmente representada como un centauro sosteniendo un arco. Sagittarius se encuentra entre Scorpius al oeste y Capricornus al este.";
	else if (A=="APS")
		return "Apus (el ave del paraíso) es una constelación del sur. Aparece por primera vez en Uranometría de Johann Bayer (año 1603), pero pudo haber sido usada por navegantes con anterioridad.";
	else if (A=="AQL")
		return "Aquila (el Águila) es una de las 48 constelaciones listadas por Ptolomeo, mencionada también por Eudoxo de Cnidos (siglo IV a. C.) y Arato (siglo III a. C.), y actualmente una de las 88 constelaciones reconocidas por la IAU. Ptolomeo catalogó diecinueve estrellas conjuntamente en esta constelación y en la constelación de Antínoo, esta última surgida durante el reinado de Adriano (117-138 d. C.). Ocupaba la parte sur de la constelación actual de Aquila hasta principios del siglo XIX, cuando fue descartada.";
	else if (A=="AQR")
		return "Acuario (el portador del Agua o ánfora), es una de las 88 constelaciones reconocidas por la astronomía moderna, descrita por Claudio Ptolomeo. Su símbolo representa el flujo del agua.\nDe todo el zodiaco, Acuario es una de las constelaciones reconocida con mayor antigüedad. Los sumerios le dieron este nombre a la constelación, en honor a su dios An, que derrama el agua de la inmortalidad sobre la Tierra. Se encuentra en una región comúnmente llamada el Mar o Aqua por su prodifusión de constelaciones acuáticas tales como Cetus, Piscis, Eridanus. Algunas veces el río Eridanus se representa como lo que derrama la vasija de Acuario.";
	else if (A=="ARA")
		return "Ara, el altar, es una constelación austral situada entre Scorpius y Triangulum Australe. Es una de las 48 constelaciones recogidas por Ptolomeo en el siglo II y una de las 88 constelaciones actuales.";
	else if (A=="VOL")
		return "Volans, el pez volador, es una constelación que sólo se puede ver, prácticamente, desde lugares localizados en el hemisferio sur terrestre (a excepción de algunos lugares en el hemisferio norte, próximos al ecuador). Esta fue una de las creaciones de los navegantes holandeses Pieter Dirkszoon Keyser y Frederick de Houtman entre los años 1595 y 1597. Apareció por primera vez en los mapas estelares preparados por el astrónomo alemán Johann Bayer publicados en Uranometria (1603).";
	else if (A=="VUL")
		return "Vulpecula, La zorra o La Raposilla, es una pequeña constelación del norte ubicada en medio del Triángulo de verano, al norte de Sagitta y Delphinus. No contiene ninguna estrella brillante.";
	else if (A=="BOO")
		return "Bootes o el Boyero es una de las 88 constelaciones modernas y era una de las 48 constelaciones listadas por Ptolomeo. Bootes parece ser una figura humana grande, mirando hacia la Osa Mayor";
	else if (A=="CAP")
		return "Capricornus (la cabra mitad pez) es una de las constelaciones del Zodíaco, llamada comúnmente Capricornio, sobre todo en lo referente a la astrología. Aunque a veces se representa como una cabra, generalmente se le añade una cola de pez.";
	else if (A=="TUC")
		return "Tucana, el tucán, es una constelación del hemisferio sur celeste. Es una de las 88 constelaciones aceptadas por la Unión Astronómica Internacional. Fue creada por los navegantes holandeses Pieter Dirkszoon Keyser y Frederick de Houtman entre 1595 y 1597, como resultado de sus exploraciones por los mares del hemisferio sur. Apareció por primera vez en la obra Uranometria (1603), de Johann Bayer. Representa al tucán, una especie de ave tropical oriunda de Suramérica.";
	else if (A=="TRA")
		return "Triangulum Australe es una pequeña constelación austral cuyas tres estrellas más brillantes, de segunda y tercera magnitud, forman casi un triángulo equilátero. Esta constelación fue introducida por Johann Bayer en 1603.\nNo debe ser confundida con la constelación boreal de Triangulum.";
	else if (A=="TEL")
		return "Telescopium o el Telescopio es una pequeña constelación del hemisferio celeste austral, una de las doce conformadas en el siglo XVIII por el astrónomo francés Nicolas-Louis de Lacaille y nombradas con instrumentos científicos.\nLa estrella más brillante de la constelación es Alfa Telescopii, una subgigante blancoazulada con una magnitud aparente de 3,5; le sigue Zeta Telescopii, una gigante naranja con 4,1 de magnitud. Eta y PZ Telescopii son dos sistemas estelares jóvenes rodeados de discos de escombros que tienen sendas enanas marrones de compañeras.";
	else
		return "Error, check for: "+A;

}