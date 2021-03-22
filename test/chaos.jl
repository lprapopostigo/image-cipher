function chaos(n, r)
    if n == 0
        return r
    else
        return 3.8 * chaos(n - 1, r) * (1 - chaos(n - 1, r))
    end
end


for n = 0:10
    x = chaos(n, 0.40)
    println(x)
    println(xor(trunc(Int, 16000 * x) % 7, 0xffffff))
    println("---------")
end
