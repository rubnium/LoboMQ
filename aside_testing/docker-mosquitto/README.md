### Based on:
- Mosquitto docker setup tutorial: https://github.com/sukesh-ak/setup-mosquitto-with-docker

### Commands:
- Run container: `docker-compose -p mqtt5 up -d`
- Create user/password:
    ```
    # login interactively into the mqtt container
    docker exec -it <container-id> sh

    # add user and it will prompt for password
    mosquitto_passwd -c /mosquitto/config/pwfile user1

    # delete user command format
    mosquitto_passwd -D /mosquitto/config/pwfile <user-name-to-delete>
    ```
### Info:
- Mosquitto user and password: rubnium - root
