## MUNGE for PHP
This is the source code for a very basic MUNGE extension for PHP. It includes the following functions, complete with exception throwing on errors:
| Function | Description | Parameters | Returns |
| -------- | ----------- | ---------- | ------- |
| `munge_php()` | Encodes a payload &c. using MUNGE. | `string` or nothing (nothing if you don't want a payload) | `string`: The MUNGE credential created from the encoded payload &c. |
| `unmunge_php()` | Decodes a MUNGE token. | `string`: The MUNGE token to be decoded. | `associative array['gid', 'uid', 'encode_time', 'decode_time', 'username']`: array containing payload and metadata from the MUNGE credential. |

## Installation
### Prerequisites:
If you run debian-based linux, install the necessary libraries with:
```sh
apt-get update && apt-get install -y \
    libtool \
    autoconf \
    automake \
    make \
    gcc \
    g++ \
    munge \
    libmunge-dev \
    vim \
    php \
    php-dev
```

### Using older versions of PHP
Keep in mind that you will need to build the extension with the same `php` and `php-dev` version and API that you intend to run the extension on. To install other versions of php, try the following:
```sh
sudo add-apt-repository ppa:ondrej/php
sudo apt update
sudo apt install phpX.Y # replace X.Y with the version you want to install (e.g. 8.2)
sudo apt install phpX.Y-dev
```

## Building the extension
Run the following to build and install the extension:
```sh
phpize # or phpizeX.Y
./configure --with-munge --enable-munge-php
make
make install # may need to run this with sudo
```
