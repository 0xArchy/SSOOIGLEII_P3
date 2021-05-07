#include "../include/Buscador.h"

int main(int argc, char **argv) {

    std::vector<std::thread> t_requests_managers;
    int shm_payment, shm_client;
    sem_t *sem_balance_ready, *sem_balance_charge, *sem_request_ready, *sem_stored_request;
    struct T_Payment *payment;
    struct TRequest_t *request;
    create_shm_segments(&shm_payment, &payment,&shm_client, &request);
    create_sems(&sem_balance_ready, &sem_balance_charge, &sem_request_ready, &sem_stored_request);
    //create_payment_system(PAYMENT_SYSTEM);

    /*We gonna simulate a simple Payment System*/
    /*payment->id = 0;
    payment->client_initial_balance = 10;
    payment->balance = 0;
    std::cout << "[BUSCADOR] manda recargar puntos un proceso con 0 de balance y 10 de initial_balance" << std::endl;
    signal_semaphore(sem_balance_ready);
    wait_semaphore(sem_balance_charge);
    std::cout << "[BUSCADOR] Saldo después de llamar a Payment_system = " << payment->balance << std::endl;
    */

    t_requests_managers.push_back(std::thread(wait_requests, sem_request_ready, sem_stored_request, request));
    //t_requests_managers.push_back(std::thread(wait_requests, sem_balance_ready, sem_balance_charge, payment));
    t_requests_managers.push_back(std::thread(manage_queue));

    /*Create one client premium test*/
    pid_t pid = fork();
    if(pid == 0){
        char *argv[] = {(char *)"CLIENT_PREMIUM",(char*)"hola",(char*)"data/prueba.txt",NULL};
        if((execv(CLIENT_PREMIUM_PATH,argv)) == -1){
            fprintf(stderr,"[BUSCADOR] Error al crear cliente.\n");
            free_resources();
            std::exit(EXIT_FAILURE);
        }
    }
    //std::this_thread::sleep_for(std::chrono::seconds(2));
    //create_payment_system(PAYMENT_SYSTEM);

    std::for_each(t_requests_managers.begin(), t_requests_managers.end(), [](std::thread& t) { t.join(); });
    //while(1);
    return EXIT_SUCCESS;
}

[[noreturn]] void manage_queue() {
    int random_number;
    bool vip, choose;
    char v_texts[MAX_BUFFER_TEXT];
    char word[MAX_BUFFER_TEXT];
    int fd_write_client;
    int initial_balance;
    char category[MAX_BUFFER_TEXT];
    int client_pid;
    std::unique_lock<std::mutex> ul(queue_semaphore_management);

    for (;;) {

        extract_request_condition.wait(ul, [] {
            return request_vector.size() > 0;
        });
        std::cout << "[HILO MANAGE QUEUE] Extraemos petición de la cola" << std::endl;

        //Randomize number in order to choose 80% request for premium clients, and 20% normal client
        random_number = 1 + rand() % (10);
        vip = (random_number <= 8 ? true : false);
        int i;

        for (i = 0; i < request_vector.size(); i++) {
            if (vip && (strncmp(request_vector[i].category,PREMIUM_CATEGORY,sizeof (request_vector[i].category))==0 ||
                    strncmp(request_vector[i].category,ILIMITED_PREMIUM_CATEGORY,sizeof (request_vector[i].category))==0 ))
                choose = true;
            else if (request_vector[i].category == NORMAL_CATEGORY) choose = true;
            if (choose) {
                strcpy(category,request_vector[i].category );
                strcpy(word,request_vector[i].word );
                fd_write_client = request_vector[i].fd_descriptor;
                initial_balance = request_vector[i].initial_balance;
                strcpy(v_texts,request_vector[i].v_texts);
                client_pid = request_vector[i].client_pid;
                memset(&request_vector[i],0,sizeof(struct TRequest_t));
                request_vector.clear(); //Remove request for queue
                create_client_management(v_texts, word,fd_write_client, initial_balance, category, client_pid);

                break;
            }
        }

        extract_request_condition.notify_one();
        /*Create process*/
        ul.unlock(); //Unlock the semaphore

    }
}
void create_client_management(char *v_texts, char *word,
                              int fd_write_client, int initial_balance, char *category, int client_pid)
{
    pid_t pid;
    char fd_write_client_str[MAX_BUFFER_TEXT];
    char initial_balance_str[MAX_BUFFER_TEXT];
    char client_pid_str[MAX_BUFFER_TEXT];
    int v_text_len;
    char *token;
    int argv_len;
    int j;
    char auxiliar_buffer[MAX_BUFFER_TEXT];
    switch((pid = fork())){
        case -1:
            fprintf(stderr,"[BUSCADOR] Error while create a client_management.\n");
            free_resources();
            std::exit(EXIT_FAILURE);
        case 0:
            /*Format integer to char* or string*/
            sprintf(fd_write_client_str,"%d",fd_write_client);
            sprintf(initial_balance_str,"%i",initial_balance);
            sprintf(client_pid_str,"%d",client_pid);

            std::cout << "categoria en create_client: " << category << std::endl;
            std::cout << "word en create_client: " << word << std::endl;

            /*Get the number of texts*/
            strncpy(auxiliar_buffer, v_texts,sizeof (v_texts)); // Copy v_text in auxilizar buffer because tokenizer delete elements
            v_text_len = gettextlen(auxiliar_buffer);
            /*Prepare the argv vector to execl*/
            argv_len = v_text_len + 7; //7 parameters, without the texts
            char *argv[argv_len];
            argv[0] = (char *)ILIMITED_PREMIUM_CATEGORY;
            argv[1] = category;
            argv[2] = word;
            argv[3] = initial_balance_str;
            argv[4] = fd_write_client_str;
            argv[5] = client_pid_str;
            j = 6;
            /*Tokenizer and get the file_name of the texts*/
            token = strtok(v_texts,"-");
            while(token!=NULL){
                argv[j++] = token;
                token = strtok(NULL, "-");
            }
            /*Finnish with NULL argv*/
            argv[j] = NULL;

            /*Finnish with execute the client manager*/
            if((execv(CLIENT_MANAGEMENT_PATH,argv)) == -1){
                fprintf(stderr,"[BUSCADOR] Error while create Client Management.\n");
                std::exit(EXIT_FAILURE);
            }
    }
}

int gettextlen(char *v_texts){
    int j = 0;
    char *token;
    token = strtok(v_texts,"-");
    while(token!=NULL){
        j++;
        token = strtok(NULL, "-");
    }
    return j;
}

[[noreturn]] void wait_requests(sem_t *sem_request_ready, sem_t *sem_stored_request,struct TRequest_t *request){

    std::unique_lock<std::mutex> ul(queue_semaphore_management);

    for(;;){

        signal_semaphore(sem_request_ready);
        std::this_thread::sleep_for(std::chrono::seconds(2));
        wait_semaphore(sem_stored_request);
        request_vector.push_back(*request);
        //std::cout << "Petición metida" << std::endl;
        ul.unlock();
    }
}


 /* Process management */
void create_clients(enum ProcessClass_t clas, int n_processes, int index_process_table)
{
    std::string *path = new std::string();
    std::string *str_process_class = new std::string();
    int i;
    pid_t pid;

    get_str_process_info(clas, path, str_process_class);

    for (i = index_process_table; i < (index_process_table + n_processes); i++) {
        pid = create_single_process(path->data(), str_process_class->data(), "");
        struct TProcess_t process;
        process.clas = clas;
        process.pid = pid;
        process.str_process_class = str_process_class->data();
        v_clients.push_back(process); // ad client to process
    }

    std::cout << "[Buscador] " << n_processes << " " << str_process_class->data() << " processes created." << std::endl;
}
void create_payment_system(enum ProcessClass_t clas)
{
    std::string *path = new std::string();
    std::string *str_process_class = new std::string();
    int i;
    pid_t pid;

    get_str_process_info(clas, path, str_process_class);

    pid = create_single_process(path->data(), str_process_class->data(), "");

    /*PAYMENT SYSTEM CREATE IN BACKGROUND*/
    std::cout << "[Buscador] " << 1 << " " << str_process_class->data() << " processes created." << std::endl;
    payment_process = pid;
}

pid_t create_single_process(std::string path, std::string clas, std::string argv)
{
    pid_t pid;

    switch (pid = fork()) {
        case -1 :
            fprintf(stderr, "[MANAGER] Error creating %s process: %s.\n",
                    clas.c_str(), strerror(errno));
            terminate_processes();
            free_resources();
            std::exit(EXIT_FAILURE);
            /* Child process */
        case 0 :
            if (execl(path.c_str(), clas.c_str(), argv.c_str(), NULL) == -1) {
                fprintf(stderr, "[MANAGER] Error using execl() in %s process: %s.\n",
                        clas.c_str(), strerror(errno));
                std::exit(EXIT_FAILURE);
            }
    }
    return pid;
}

void get_str_process_info(enum ProcessClass_t clas, std::string *path, std::string *str_process_class)
{
    switch (clas) {
        case CLIENT:
            *path = CLIENT_PATH;
            *str_process_class =  CLIENT_CLASS;
        break;
        case PAYMENT_SYSTEM:
            *path = PAYMENT_SYSTEM_PATH;
            *str_process_class = PAYMENT_SYSTEM_CLASS;
        break;
    }
}


/* Semaphores and shared memory management */
void create_shm_segments(int *shm_payment, struct T_Payment **p_payment, int *shm_client, struct TRequest_t **p_request)
{
    /* Create and initialize shared memory segments */
    *shm_payment = shm_open(SHM_PAYMENT, O_CREAT | O_RDWR, 0644);
    ftruncate(*shm_payment, sizeof(struct T_Payment));
    *p_payment = static_cast<T_Payment *>(mmap(NULL, sizeof(struct T_Payment),
            PROT_READ | PROT_WRITE, MAP_SHARED, *shm_payment, 0));

    *shm_client = shm_open(SHM_CLIENT, O_CREAT | O_RDWR, 0644);
    ftruncate(*shm_client, sizeof(struct TRequest_t));
    *p_request = static_cast<TRequest_t *>(mmap(NULL, sizeof(struct TRequest_t),
                                                PROT_READ | PROT_WRITE, MAP_SHARED, *shm_client, 0));
}
void create_sems(sem_t **sem_balance_ready, sem_t **sem_balance_charge, sem_t **sem_request_ready, sem_t **sem_stored_request)
{
    *sem_balance_ready = create_semaphore(SEM_BALANCE_READY,0);
    *sem_balance_charge = create_semaphore(SEM_BALANCE_CHARGE,0);
    *sem_request_ready = create_semaphore(SEM_REQUEST_READY,0);
    *sem_stored_request = create_semaphore(SEM_STORED_REQUEST,0);
}
void close_shared_memory_segments(int shm_payment, int shm_client)
{
    close(shm_payment);
    close(shm_client);
}
void terminate_processes()
{
    int i;

    /*First We kill the PaymentSystem Process*/
    if (kill(payment_process, SIGINT) == -1) {
        fprintf(stderr, "[BUSCADOR] Error using kill() on process %d: %s.\n",
                payment_process, strerror(errno));
    }
    /*Next We kill Clients Processes*/
    std::cout << "\n----- [BUSCADOR] Terminating running child processes ----- " << std::endl;
    for (i = 0; i < v_clients.size(); i++) {
        /* Child process alive */
        if (v_clients[i].pid != 0) {
            std::cout << "[BUSCADOR] Terminating " << v_clients[i].str_process_class <<
            " process [" << v_clients[i].pid << "]..." << std::endl;
            if (kill(v_clients[i].pid, SIGINT) == -1) {
                fprintf(stderr, "[BUSCADOR] Error using kill() on process %d: %s.\n",
                        v_clients[i].pid, strerror(errno));
            }
        }
    }
}
void free_resources()
{
    std::cout << "\n----- [BUSCADOR] Free resources ----- " << std::endl;

    v_clients.clear();

    /* Semaphores */
    remove_semaphore(SEM_BALANCE_READY);
    remove_semaphore(SEM_BALANCE_CHARGE);
    remove_semaphore(SEM_REQUEST_READY);
    remove_semaphore(SEM_STORED_REQUEST);

    /* Shared memory segments*/
    shm_unlink(SHM_PAYMENT);
    shm_unlink(SHM_CLIENT);
}

void install_signal_handler(){
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        fprintf(stderr, "[MANAGER] Error installing signal handler: %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}
void signal_handler(int signal){
    std::cout << "[BUSCADOR] Exiting...";
    free_resources();
}


