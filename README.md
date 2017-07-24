# Zenomorph8
An homomorphic encryption single file encrypter in plain ECMAScript (Javascript). For now only encrypts 8 bits integers (UTF8 works fine too with one extension like for japanese characters).

## Usage

Include the file in anyway you want. Then use :

```javascript
key = [153,123,12,52]; // Any number under 255 is fine, higher number put you at risk of loss of precision. Any length is fine.
salt = [31,25,65,14]; // Same as for the key, but the length needs to match the one of the key. This requirement may be suppressed.

line = "This will be encrypted even in 日本語(japanese) ";

my_array = line.split("").map(function(char) {
  return char.charCodeAt(0);
  });

cipher = crypt8(my_array,key,salt);
// cipher now contains an array of floating points numbers
// I forgot the '.' at the end, lets change the space to a period. A space is 32, a period 46.
cipher=add8(cipher,44,18,key,salt); // key is used only for generating a cipher of 18. this will be implemented next as 2 function, 1 to generate a ciphered  delta and one for applying it.
deciphered = decrypt8(cipher,key,salt);

my_result = "";
deciphered.map(function(char) {
  my_result+=String.fromCharCode(char);
});

// my_result now contains "This will be encrypted even in 日本語(japanese)." (notice the period)
```

The behaviour is OK with numbers below 2^15 even with multiplication.

If you manage to decipher this without the key, contact me ASAP :
```json
[0.94169999999999998, 8.0808, 2.0608, 8.5565999999999995, 1.4319000000000002, 8.3868000000000009, 2.0608, 8.5244, 1.3028999999999999, 7.9787999999999997, 2.1899999999999999, 8.1471999999999998, 1.4964, 8.1216000000000008, 2.1995, 8.5289999999999999, 0.4128, 7.4892000000000003, 2.0608, 8.4461999999999993, 1.4060999999999999, 6.6528, 2.1842999999999999, 8.5060000000000002, 0.4128, 8.1419999999999995, 2.1899999999999999, 8.4830000000000005, 1.4319000000000002, 8.3663999999999987, 2.0874000000000001, 8.1471999999999998, 1.0707, 8.0603999999999996, 2.2090000000000001, 8.4600000000000009, 0.4128, 8.2235999999999994, 2.1919, 8.1471999999999998, 1.4964, 8.1216000000000008, 2.1995, 8.5289999999999999, 0.4128, 8.2644000000000002, 2.2090000000000001, 8.1471999999999998, 0.8256, 7.5503999999999998, 2.2223000000000002, 8.4600000000000009, 1.4319000000000002, 8.4071999999999996, 2.1995, 8.4554000000000009, 0.98040000000000005, 7.9787999999999997, 2.1957, 8.1471999999999998, 1.4319000000000002, 8.2439999999999998, 2.0608, 8.3864000000000001, 1.5351000000000001, 8.1419999999999995, 2.2204000000000002, 8.5335999999999999, 1.3028999999999999, 8.3255999999999997, 2.0608, 8.2667999999999999, 0.4128, 7.8360000000000003, 2.1463000000000001, 8.2576000000000001, 1.032, 7.5503999999999998, 2.1501000000000001, 8.4047999999999998, 0.59340000000000004, 6]
```

The salt for this is : `[0,6,2,8]`