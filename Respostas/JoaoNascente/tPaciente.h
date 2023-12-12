#ifndef _TPACIENTE_H
#define _TPACIENTE_H

typedef struct tPaciente tPaciente;

enum tipoPele
{
    I,
    II,
    III,
    IV,
    V,
    VI
};

void *cria_paciente();

void consultaPaciente(void *paciente,
                      int possui_diabetes,
                      int fuma,
                      int possui_alergia,
                      int possui_historico_cancer,
                      enum tipoPele tipoPele);

void adiciona_lesao(void *paciente, void *l);

void desaloca_paciente(void *paciente);

#endif