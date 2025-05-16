2025-01-07  
Resources used:  
[WebDAV Server Setup on Ubuntu Linux](https://linuxconfig.org/webdav-server-setup-on-ubuntu-linux)

#### Initial Setup
1. Install Apache and verify the _Apache2 Default Page_ can be reached at http://\<server-static-ip-address\>. For information on how to set up a static IP on Ubuntu Linux, go to [static-ip-setup](./static-ip-setup.md).
```
$ sudo apt install apache2
```

2. Disable the _Apache Default Page_ and reload Apache.
```
$ sudo a2dissite 000-default
$ sudo service apache2 reload
```

#### Preparing Our Own Default Page
3. Configure Virtual Host: create a configuration file
```
$ cd /etc/apache2/sites-available/
$ sudo vim webdav.local.conf
```
Add the following content:
```
<VirtualHost *:80>
	ServerAdmin webmaster@localhost
	ServerName webdav.local
	
	DocumentRoot /var/www/webdav
	<Directory />
		Options FollowSymLinks
		AllowOverride None
	</Directory>
	<Directory /var/www/webdav>
		Options Indexes FollowSymLinks MultiViews
		AllowOverride None
		Order allow,deny
		allow from all
	</Directory>
</VirtualHost>
```

4. Create a webdav directory and index.html file, and set ownership. Note: for the second command, if we try to run `sudo echo "<message>" > /var/www/webdav/index.html`, we get permission denied. For the third command, we are setting owner and group with owner:group `www-data:www-data`.
```
$ sudo mkdir /var/www/webdav
$ sudo sh -c 'echo "Welcome from WebDAV.local" > /var/www/webdav/index.html'
$ sudo chown www-data:www-data /var/www/webdav
```

5. Navigate to http://\<server-static-ip-address\> to test new Default Page.

#### Enable WebDAV Module
6. Enable module
```
$ sudo a2enmod dav_fs
```

7. Create a directory for WebDAV data and a data file for testing.
```
$ sudo mkdir /var/www/webdav/svn
$ sudo touch /var/www/webdav/svn/linuxconfig.txt
$ sudo chown www-data:www-data /var/www/webdav/svn
```

8. Navigate to and open /etc/apache2/sites-available/webdav.local.conf.
```
$ cd /etc/apache2/sites-available/
$ sudo vim webdav.local.conf
```

9. Add the _Alias_ content at the bottom.
```
<VirtualHost *:80>
	ServerAdmin webmaster@localhost
	ServerName webdav.local
	
	DocumentRoot /var/www/webdav
	<Directory />
		Options FollowSymLinks
		AllowOverride None
	</Directory>
	<Directory /var/www/webdav>
		Options Indexes FollowSymLinks MultiViews
		AllowOverride None
		Order allow,deny
		allow from all
	</Directory>
	Alias /svn /var/www/webdav/svn
	<Location /svn>
		DAV On
	</Location>
</VirtualHost>
```

10. Restart Apache and test changes by navigating to http://\<server-static-ip-address\>/svn.
```
$ sudo service apache2 restart
```

#### Set Up User Authentication
11. Create new directory in /usr/local/ and add new user. You'll be prompted to create a new password.
```
$ sudo mkdir /usr/local/apache2/
$ sudo htpasswd -c /usr/local/apache2/webdav.passwords linuxconfig
```

12. Add AuthType, AuthName, AuthUserFile, and Require rule to <Location /svn> in Virtual Host config file, webdav.local.config.
```
$ sudo vim /etc/apache2/sites-available/webdav.local.config
```
Add the shit below _DAV On_.
```
<Location /svn>
	DAV On
	AuthType Basic
	AuthName "webdav"
	AuthUserFile /usr/local/apache2/webdav.passwords
	Require valid-user
</Location>
```

13. Restart Apache and test that credentials are required. Your browsers cache may need to be cleared.
```
$ sudo service apache2 restart
```

#### Mount WebDAV Directory
14. Install davfs2, which will ask if non-root users should have permission to mount webdav resources. Select _No_. This can always be changed later by running the command `dpkg-reconfigure davfs2`.
```
$ sudo apt install davfs2
```

15. Create and test the mount point.
```
$ sudo mkdir /mnt/webdav
$ sudo mount.davfs http://<server-static-ip-address>/svn /mnt/webdav/
```

```
$ cd /mnt/webdav/
$ ls
```

#### Secure with HTTPS (Not Optional)
16. 