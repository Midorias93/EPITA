package com.epita.creeps.utils;

import com.epita.creeps.unit.myUnit;
import com.mashape.unirest.http.HttpResponse;
import com.mashape.unirest.http.JsonNode;

import java.util.concurrent.CompletableFuture;

public class Pair {
    public myUnit key;
    public CompletableFuture<com.mashape.unirest.http.HttpResponse<com.mashape.unirest.http.JsonNode>> value;
    public Pair(myUnit key, CompletableFuture<HttpResponse<JsonNode>> value) {
        this.key = key;
        this.value = value;
    }
}
