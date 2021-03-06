/******************************************************
* Project : Práctica 3 de Sistemas Operativos II
*
* Program name : PaymentSystem.cpp
*
* Author : Tomás Jesús García López y Sergio Sánchez Iglesias
*
* Date created : 21/04/2021
*
* Purpose : PaymentSystem para recargar los creditos a un cliente Premium Limitado
*
*
* Revision History:
*
* Date          Author          Ref      Revision
* 10/05/2021    Tomás          1         Formateado mensaje a mostrar
*
|********************************************************/

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#include "../include/PaymentSystem.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main(int argc, char **args)
{
    struct TPayment *payment;
    int shm_payment;
    sem_t *p_sem_balance_ready, *p_sem_balance_charge;

    /* Get shared memory segments and semaphores */
    get_shm_segments(&shm_payment, &payment);
    get_sems(&p_sem_balance_ready, &p_sem_balance_charge);

    /* Will work until killed by the buscador */
    for(;;) {
        get_and_process_task(p_sem_balance_ready, p_sem_balance_charge, payment);
    }

    return EXIT_SUCCESS;
}

/********************************* SEMAPHORES AND SHARED MEMORY MANAGEMENT ********************************************/

void get_shm_segments(int *shm_payment, struct TPayment **p_payment)
{
    *shm_payment = shm_open(SHM_PAYMENT, O_RDWR, 0644);
    *p_payment = static_cast<TPayment *>(mmap(nullptr, sizeof(struct TPayment),
                                               PROT_READ | PROT_WRITE, MAP_SHARED, *shm_payment, 0));
}

void get_sems(sem_t **p_sem_balance_ready, sem_t **p_sem_balance_charge)
{
    *p_sem_balance_ready = get_semaphore(SEM_BALANCE_READY);
    *p_sem_balance_charge = get_semaphore(SEM_BALANCE_CHARGE);
}

/********************************* TASK MANAGEMENT ********************************************************************/

void get_and_process_task(sem_t *p_sem_balance_ready, sem_t *p_sem_balance_charge,
                          struct TPayment *p_payment)
{
    /* Rendezvouz patron to charge the clients credits */
    wait_semaphore(p_sem_balance_ready);

    p_payment->balance = p_payment->client_initial_balance;
    std::cout << BOLDBLUE << "[PAYMENT_SYSTEM] Client " << RESET
        << BOLDYELLOW <<  p_payment->id << RESET << " Has been charge with " << BOLDGREEN
        << p_payment->balance << RESET << " credits" << std::endl;

    signal_semaphore(p_sem_balance_charge);
}


#pragma clang diagnostic pop