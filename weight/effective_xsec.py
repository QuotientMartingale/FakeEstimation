import os
#import ROOT

# Arrays of DSIDs
# Ztautau
ZttQCD = [344772, 344774, 344775, 344776, 344778, 344779, 344780, 344781, 344782, 364137, 364138, 364139, 364140, 364141, 364210, 364211, 364212, 364213, 364214, 364215]
ZttEWK = [308094, ]
# Ztt = ZttQCD + ZttEWK
Ztt = [344772, 344774, 344775, 344776, 344778, 344779, 344780, 344781, 344782, 364137, 364138, 364139, 364140, 364141, 364210, 364211, 364212, 364213, 364214, 364215, 308094]
# Single-Top and ttbar
Top = [410470, 410471, 410644, 410645, 410646, 410647, 410658, 410659, 410155, 410218, 410219, 410220, 412043, 304014]
# Diboson
VV = [363355, 363356, 363357, 363358, 363359, 363489, 363494, 364250, 364253, 364254, 364255, 364288, 364289, 364290]
# W(tau/mu/e + nu) + jets
W = [364156, 364157, 364158, 364159, 364160, 364161, 364162, 364163, 364164, 364165, 364166, 364167, 364168, 364169, 364170, 364171, 364172, 364173, 364174, 364175, 364176, 364177, 364178, 364179, 364180, 364181, 364182, 364183, 364184, 364185, 364186, 364187, 364188, 364189, 364190, 364191, 364192, 364193, 364194, 364195, 364196, 364197, 308096, 308097, 308098]
# Zll + jets
ZllQCD = [345099, 345100, 345101, 345102, 364100, 364101, 364102, 364103, 364104, 364105, 364106, 364107, 364108, 364109, 364110, 364111, 364112, 364113, 364114, 364115, 364116, 364117, 364118, 364119, 364120, 364121, 364122, 364123, 364124, 364125, 364126, 364127, 364198, 364199, 364200, 364201, 364202, 364203, 364204, 364205, 364206, 364207, 364208, 364209]
ZllEWK = [308092, 308093]
#Zll = ZllQCD + ZllEWK
Zll = [345099, 345100, 345101, 345102, 364100, 364101, 364102, 364103, 364104, 364105, 364106, 364107, 364108, 364109, 364110, 364111, 364112, 364113, 364114, 364115, 364116, 364117, 364118, 364119, 364120, 364121, 364122, 364123, 364124, 364125, 364126, 364127, 364198, 364199, 364200, 364201, 364202, 364203, 364204, 364205, 364206, 364207, 364208, 364209, 308092, 308093]
ggHWW = [345324, ]
VBFHWW = [345948, ]
# other_bkg = VV + W + Zll + ggHWW + VBFHWW
other_bkg = [363355, 363356, 363357, 363358, 363359, 363489, 363494, 364250, 364253, 364254, 364255, 364288, 364289, 364290, 364156, 364157, 364158, 364159, 364160, 364161, 364162, 364163, 364164, 364165, 364166, 364167, 364168, 364169, 364170, 364171, 364172, 364173, 364174, 364175, 364176, 364177, 364178, 364179, 364180, 364181, 364182, 364183, 364184, 364185, 364186, 364187, 364188, 364189, 364190, 364191, 364192, 364193, 364194, 364195, 364196, 364197, 308096, 308097, 308098, 345099, 345100, 345101, 345102, 364100, 364101, 364102, 364103, 364104, 364105, 364106, 364107, 364108, 364109, 364110, 364111, 364112, 364113, 364114, 364115, 364116, 364117, 364118, 364119, 364120, 364121, 364122, 364123, 364124, 364125, 364126, 364127, 364198, 364199, 364200, 364201, 364202, 364203, 364204, 364205, 364206, 364207, 364208, 364209, 308092, 308093, 345324, 345948]
# Signal samples
ggH = [345121, 345122, 345123]
VBFH = [346191, 346192, 346193]
WH = [345211, 345212]
ZH = [345217]
ttH = [346343, 346344, 346345]
# signal_SM = ggH + VBFH + WH + ZH + ttH
signal_SM = [345121, 345122, 345123, 346191, 346192, 346193, 345211, 345212, 345217, 346343, 346344, 346345]

ggH_CPodd = [346527, 346528, 346562]
VBFH_CPodd = [346565, 346566, 346571]
# signal_CPodd = ggH_CPodd + VBFH_CPodd
signal_CPodd = [346527, 346528, 346562, 346565, 346566, 346571]

ggH_unpol = [346531, 346532, 346564]
VBFH_unpol = [346569, 346570, 346573]
WH_unpol = [346909, 346912]
ZH_unpol = [346915, ]
ttH_unpol = [346919, 346923, 346927]
# Signal_unpol = ggH_unpol + VBFH_unpol + WH_unpol + ZH_unpol + ttH_unpol
signal_unpol = [346531, 346532, 346564, 346569, 346570, 346573, 346909, 346912, 346915, 346919, 346923, 346927]

ggH_He7 = [600565, 600566, 600567, 600568]
VBFH_He7 = [600569, 600570, 600571, 600572]
WH_He7 = [600573, 600574]
ZH_He7 = [600575, ]
ttH_afii = [346343, 346344, 346345]
ttH_afii_ME = [346443, 346444, 346445]
ttH_afii_PS = [346346, 346347, 346348]

all = [344772, 344774, 344775, 344776, 344778, 344779, 344780, 344781, 344782, 364137, 364138, 364139, 364140, 364141, 364210, 364211, 364212, 364213, 364214, 364215, 308094, 410470, 410471, 410644, 410645, 410646, 410647, 410658, 410659, 410155, 410218, 410219, 410220, 412043, 304014, 363355, 363356, 363357, 363358, 363359, 363489, 363494, 364250, 364253, 364254, 364255, 364288, 364289, 364290, 364156, 364157, 364158, 364159, 364160, 364161, 364162, 364163, 364164, 364165, 364166, 364167, 364168, 364169, 364170, 364171, 364172, 364173, 364174, 364175, 364176, 364177, 364178, 364179, 364180, 364181, 364182, 364183, 364184, 364185, 364186, 364187, 364188, 364189, 364190, 364191, 364192, 364193, 364194, 364195, 364196, 364197, 308096, 308097, 308098, 345099, 345100, 345101, 345102, 364100, 364101, 364102, 364103, 364104, 364105, 364106, 364107, 364108, 364109, 364110, 364111, 364112, 364113, 364114, 364115, 364116, 364117, 364118, 364119, 364120, 364121, 364122, 364123, 364124, 364125, 364126, 364127, 364198, 364199, 364200, 364201, 364202, 364203, 364204, 364205, 364206, 364207, 364208, 364209, 308092, 308093, 345324, 345948, 345121, 345122, 345123, 346191, 346192, 346193, 345211, 345212, 345217, 346343, 346344, 346345, 346527, 346528, 346562, 346565, 346566, 346571, 346531, 346532, 346564, 346569, 346570, 346573, 346909, 346912, 346915, 346919, 346923, 346927, 600565, 600566, 600567, 600568, 600569, 600570, 600571, 600572, 600573, 600574, 600575, 346343, 346344, 346345, 346443, 346444, 346445, 346346, 346347, 346348]

### calculate effective xsec for each dsid
Test = Test1
xsec_dict = {}
for line in open("../dataset/PMGxsecDB_mc16.txt"):
    if int((line.split()[0]).strip()) in Test:
        xsec_dict[int((line.split()[0]).strip())] = float((line.split()[1]).strip()) * float((line.split()[2]).strip()) * float((line.split()[3]).strip())
     ### str.split() return a list, str.strip() delete all special character, int() & float() transfer str to int & float

# print(xsec_dict)

with open("../dataset/eff_xsec.txt", "w") as f:
    for id in Test:
        f.write("{0}\t{1}\n".format(str(id), str(xsec_dict[id])))