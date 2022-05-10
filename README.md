# ur4ndom

Getting [perfect randomness](https://xkcd.com/221/) from your kernel.

## Usage

```sh
make
sudo insmod ur4ndom.ko
head /dev/ur4ndom
```

Example output:

```sh
$ head /dev/ur4ndom 
4
4
4
4
4
4
4
4
4
4
```