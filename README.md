# Qontainer
Repository per il progetto di Programmazione a Oggetti, anno accademico 2018/2019

Per la gerarchia, pensavo ad una specie di menu. Classe base astratta MenuItem(magari un metodo virtuale puro calorie(), pensa a qualcosa), da cui derivano Bevanda (concreta) e Pietanza (bho). Da Bevanda deriva BevandaAlcolica(astratta, metodo virtuale puro gradazioneAlcolica()), da cui derivano Liquore (concreta, gradazioneAlcolica ritorna un numero fisso per ogni istanza) e Cocktail (concreta, ha la ricetta come lista di coppie ingrediente-quantità, gradazioneAlcolica ritorna un numero calcolato in base alla ricetta). Per pietanza possiamo parlarne.
