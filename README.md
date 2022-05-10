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

*Much* better than other randomness sources:

```
pv </dev/ur4ndom >/dev/null
8.11GiB 0:00:06 [1.35GiB/s]
```

Compare that to the extremely slow `/dev/urandom`:

```
pv </dev/urandom >/dev/null
1.97GiB 0:00:04 [ 505MiB/s]
```


# Obviously don't use this for anything other than fun

This is a joke.