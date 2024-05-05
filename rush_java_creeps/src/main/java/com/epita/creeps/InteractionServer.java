package com.epita.creeps;

import com.epita.creeps.given.exception.NoReportException;
import com.epita.creeps.given.extra.Cartographer;
import com.epita.creeps.given.json.Json;
import com.epita.creeps.given.vo.report.*;
import com.epita.creeps.given.vo.response.CostResponse;
import com.epita.creeps.given.vo.response.InitResponse;
import com.mashape.unirest.http.HttpResponse;
import com.mashape.unirest.http.JsonNode;
import com.mashape.unirest.http.Unirest;
import com.mashape.unirest.http.exceptions.UnirestException;

import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;

public class InteractionServer {
    enum reportName {
        move,
        observe,
        gather,
        farm,
        build,
        other
    }

    public static HttpResponse<JsonNode> init(String[] args) {
        String URL = "http://" + args[0] + ":" + args[1] + "/init/" + args[2];
        try {
            return Unirest.post(URL).body("{}").asJson();
        } catch (UnirestException e) {
            throw new RuntimeException(e);
        }
    }

    public static HttpResponse<JsonNode> getReport(String reportId, String[] args) throws UnirestException {
        String URL = "http://" + args[0] + ":" + args[1] + "/report/" + reportId;
        return Unirest.get(URL).asJson();
    }

    public static boolean canDoTheAction(InitResponse info, CostResponse action, int actualTick) {
        return true;
    }

    static Report Get(CompletableFuture<HttpResponse<JsonNode>> futureReport, reportName command) throws ExecutionException, InterruptedException, NoReportException {
        if (futureReport != null) {
            if (command == reportName.move) {
                Report report = Json.parseReport(futureReport.get().getBody().toString());
                if (report != null)
                    Cartographer.INSTANCE.register((MoveReport) report);
                return report;
            } else if (command == reportName.build) {
                Report report = Json.parseReport(futureReport.get().getBody().toString());
                if (report != null)
                    Cartographer.INSTANCE.register((BuildReport) report);
                return report;
            } else if (command == reportName.observe) {
                Report report = Json.parseReport(futureReport.get().getBody().toString());
                if (report != null)
                    Cartographer.INSTANCE.register((ObserveReport) report);
                return report;
            } else if (command == reportName.gather) {
                Report report = Json.parseReport(futureReport.get().getBody().toString());
                if (report != null)
                    Cartographer.INSTANCE.register((GatherReport) report);
                return report;
            } else if (command == reportName.farm) {
                Report report = Json.parseReport(futureReport.get().getBody().toString());
                if (report != null)
                    Cartographer.INSTANCE.register((FarmReport) report);
                return report;
            } else {
                return Json.parseReport(futureReport.get().getBody().toString());
            }
        }
        return null;
    }
}
