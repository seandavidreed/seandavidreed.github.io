2025-02-12

OS/Distro: Ubuntu 24.04.1 LTS

Resources Used:
[Fix Docker Container DNS Internet Issues](https://confidence.sh/blog/fix-docker-container-dns-internet-issues/)

#### Notes
1. If fetches are ignored `ign` or errors result when running `docker build -t \<name\> .`, check to see if DNS servers are configured for docker.
2. Go to `/etc/docker/daemon.json`. Create it if it doesn't exist.

```bash
$ cd /etc/docker
$ vim daemon.json
```

3. Add the following json object to the file.

```json
{
    "dns": ["8.8.8.8", "1.1.1.1"]
}
```

4. Restart the docker daemon and verify it restarted.

```bash
$ sudo systemctl restart docker
$ sudo systemctl status docker
```

The final command should show that it has been active since a few seconds ago. Something like this:

```
Active: active (running) since Wed 2025-02-12 16:28:01 PST; 7s ago
```

5. Done!
