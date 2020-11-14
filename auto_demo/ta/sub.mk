global-incdirs-y += include
#global-incdirs-y += ../host/include
srcs-y += AutoTaDebug.c
srcs-y += AutoTaBase.c
srcs-y += AutoTaAes.c
srcs-y += AutoTaHash.c
srcs-y += AutoTaPbkdf2.c
srcs-y += AutoTaRsa.c
srcs-y += AutoTaHandle.c
srcs-y += AutoTaCryptoHandle.c
srcs-y += AutoTaEntry.c
# To remove a certain compiler flag, add a line like this
#cflags-template_ta.c-y += -Wno-strict-prototypes
